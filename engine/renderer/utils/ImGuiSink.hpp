#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <vector>
#include <string>
#include <mutex>

namespace Quirk::Engine::Renderer::Utils
{
   // Custom ImGui Sink for spdlog
   template<typename Mutex>
   class ImGuiSink : public spdlog::sinks::base_sink<Mutex>
   {
   public:
      ImGuiSink(){}

      std::vector<std::string>& GetLogMessages()
      {
         return log_messages_;
      }

   protected:
      void sink_it_(const spdlog::details::log_msg& msg) override
      {
         std::lock_guard<Mutex> lock(this->mutex_);
         spdlog::memory_buf_t formatted;
         this->formatter_->format(msg, formatted);
         log_messages_.emplace_back(formatted.data(), formatted.size());
      }

      void flush_() override
      {
         // No special flushing needed
      }

   private:
      std::vector<std::string> log_messages_;
      Mutex mutex_;
   };

   using ImGuiSink_mt = ImGuiSink<std::mutex>;

   // Helper function to create a shared pointer to the custom sink
   inline std::shared_ptr<ImGuiSink<std::mutex>> make_imgui_sink()
   {
      return std::make_shared<ImGuiSink<std::mutex>>();
   }

   // Initialize spdlog with the custom sink
   inline void init_logging()
   {
      auto imgui_sink = make_imgui_sink();
      auto logger = std::make_shared<spdlog::logger>("logger", imgui_sink);
      spdlog::set_default_logger(logger);
      spdlog::set_level(spdlog::level::trace);
   }
}

