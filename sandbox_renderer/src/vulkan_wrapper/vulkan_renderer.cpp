#include "vulkan_wrapper/vulkan_renderer.h"
#include <stdexcept>
#include <array>
#include <cassert>


VkSandboxRenderer::VkSandboxRenderer(VkSandboxDevice& device, SandboxWindow& window)
    : m_device(device),
    m_window(window)
{
    recreateSwapchain();
}

VkSandboxRenderer::~VkSandboxRenderer() {
    freeCommandBuffers();
}


void VkSandboxRenderer::recreateSwapchain() {

    auto extent = m_window.getExtent();
    while (extent.width == 0 || extent.width == 0)
    {
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(m_device.device());

    if (m_swapchain == nullptr) {
    
        m_swapchain = std::make_unique<VkSandboxSwapchain>(
            m_device,
            extent
        );
    }
    else {
        std::shared_ptr oldSwapchain = std::move(m_swapchain);
        m_swapchain = std::make_unique<VkSandboxSwapchain>(m_device, extent, oldSwapchain);
        if (!oldSwapchain->compareSwapFormats(*m_swapchain.get())) {
            throw std::runtime_error("Swap chain image(or depth) format has changed");
        }
    }
    createCommandBuffers();
}

ISandboxRenderer::FrameContext VkSandboxRenderer::beginFrame() {

 
    m_swapchain->acquireNextImage(&m_currentImageIndex);


    VkCommandBuffer cmd = m_commandBuffers[m_currentImageIndex];
  
    vkResetCommandBuffer(cmd, 0);

    VkCommandBufferBeginInfo beginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
    if (vkBeginCommandBuffer(cmd, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin recording command buffer");
    }
 

    m_bIsFrameStarted = true;
    m_currentFrameIndex = m_currentImageIndex;

    FrameContext ctx{};
    ctx.commandBuffer = cmd;
    return ctx;
}


void VkSandboxRenderer::endFrame() {

    assert(m_bIsFrameStarted && "Can't call endFrame while frame is not in progress");
    
    auto commandBuffer = getCurrentCommandBuffer();
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to record command buffer!");
    }
    auto result = m_swapchain->submitCommandBuffers(&commandBuffer, &m_currentImageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
        m_window.wasWindowResized()) {
        m_window.resetWindowResizedFlag();
        recreateSwapchain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to present swap chain image!");
    }


    m_bIsFrameStarted = false;
    m_currentFrameIndex = (m_currentFrameIndex + 1) % VkSandboxSwapchain::MAX_FRAMES_IN_FLIGHT;
}
void VkSandboxRenderer::beginSwapChainRenderPass(FrameContext& frame)
{
    assert(m_bIsFrameStarted && "Can't call beginSwapChainRenderPass if frame is not in progress");
 

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_swapchain->getRenderPass();
    renderPassInfo.framebuffer = m_swapchain->getFrameBuffer(m_currentImageIndex);

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = m_swapchain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { 0.5f, 0.5f, 0.5f, 1.0f };
    clearValues[1].depthStencil = { 1.0f, 0 };
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(frame.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_swapchain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(m_swapchain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{ {0, 0}, m_swapchain->getSwapChainExtent() };
    vkCmdSetViewport(frame.commandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(frame.commandBuffer, 0, 1, &scissor);
}

void VkSandboxRenderer::endSwapChainRenderPass(FrameContext& frame)
{
  
    assert(m_bIsFrameStarted && "Can't call endSwapChainRenderPass if frame is not in progress");
    
    vkCmdEndRenderPass(frame.commandBuffer);
}
void VkSandboxRenderer::createCommandBuffers() {
    size_t imageCount = m_swapchain->imageCount();
    m_commandBuffers.resize(imageCount);
    //m_commandBuffers.resize(VkSandboxSwapchain::MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = m_device.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    if (vkAllocateCommandBuffers(
        m_device.device(),
        &allocInfo,
        m_commandBuffers.data()
    ) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void VkSandboxRenderer::freeCommandBuffers() {
    if (m_commandBuffers.empty()) {
        return;
    }

    vkFreeCommandBuffers(
        m_device.device(),
        m_device.getCommandPool(),
        static_cast<uint32_t>(m_commandBuffers.size()),
        m_commandBuffers.data()
    );

    m_commandBuffers.clear();
}

void VkSandboxRenderer::waitDeviceIdle() {
    vkDeviceWaitIdle(m_device.device());
}


