#pragma once

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include <vector>
#include <memory>

namespace Quirk::Engine::Rhi
{
    /// <summary>
    /// Wrapper for vulkan debugging, creation and deletion are left up to the instance 
    /// for simplicity
    /// </summary>
    class RhiValidation
    {
    public:
        RhiValidation() = default;

        ~RhiValidation() = default;

        RhiValidation(const RhiValidation&) = delete;

        RhiValidation& operator=(const RhiValidation&) = delete;

        /// <summary>
        /// Ensures that the validation layers are enabled and supported
        /// </summary>
        /// <returns></returns>
        inline bool enableValidationLayers() const
        {
            return m_enableValidationLayers;
        }

        /// <summary>
        /// Gets the validation layers
        /// </summary>
        /// <returns>current validation layers</returns>
        inline std::vector<const char*> getValidationLayers() const
        {
            return m_validationLayers;
        }

        /// <summary>
        /// Returns the debug messenger
        /// </summary>
        /// <returns>The debug messenger</returns>
        inline VkDebugUtilsMessengerEXT& getDebugMessenger()
        {
            return m_debugMessenger;
        }
        
        /// <summary>
        /// Populates the debug messenger create info
        /// </summary>
        /// <param name="debugCreateInfo"></param>
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
        {
            debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

            debugCreateInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

            debugCreateInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

            debugCreateInfo.pfnUserCallback = debugCallback;
            debugCreateInfo.pUserData = nullptr;
        }

        /// <summary>
        /// Queries the address for the creation of the debug messenger
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="pCreateInfo"></param>
        /// <param name="pAllocator"></param>
        /// <param name="pDebugMessenger"></param>
        /// <returns></returns>
        inline static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
        {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            return func != nullptr ?
                func(instance, pCreateInfo, pAllocator, pDebugMessenger) :
                VK_ERROR_EXTENSION_NOT_PRESENT;
        }

        /// <summary>
        /// Queries the address for the destruction of the debug messenger
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="debugMessenger"></param>
        /// <param name="pAllocator"></param>
        inline static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
                func(instance, debugMessenger, pAllocator);
        }

        /// <summary>
        /// Checks to see if the validation layers are supported
        /// </summary>
        /// <returns></returns>
        bool checkValidationLayerSupport()
        {
            uint32_t count{};
            vkEnumerateInstanceLayerProperties(&count, nullptr);

            std::vector<VkLayerProperties> availableLayers(count);
            vkEnumerateInstanceLayerProperties(&count, availableLayers.data());

            const uint32_t max{ 2048 };
            for (const auto layerName : m_validationLayers)
            {
                bool layerFound{ false };

                for (const auto& layerProperties : availableLayers)
                {
                    if (strncmp(layerName, layerProperties.layerName, max) == 0)
                    {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound)
                    return false;
            }

            return true;
        }

    private:

        /// <summary>
        /// Determines the severity of the message and logs it
        /// </summary>
        /// <param name="messageSeverity"></param>
        /// <param name="messageType"></param>
        /// <param name="pCallbackData"></param>
        /// <param name="pUserData"></param>
        /// <returns></returns>
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData)
        {
            switch (messageSeverity)
            {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                spdlog::trace("validation layer: {}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                spdlog::info("validation layer: {}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                spdlog::warn("validation layer: {}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                spdlog::error("validation layer: {}", pCallbackData->pMessage);
                break;
            }
            return VK_FALSE;
        }

    private:
        std::vector<const char*> m_validationLayers{ "VK_LAYER_KHRONOS_validation" };
        static VkDebugUtilsMessengerEXT m_debugMessenger;

#ifdef DEBUG
        const bool m_enableValidationLayers{ true };
#else
        const bool m_enableValidationLayers{ false };
#endif // DEBUG
    };
}
