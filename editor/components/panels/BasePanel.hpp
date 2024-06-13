#pragma once
#include "../Component.hpp"
#include <string>

namespace Quirk::Editor::Components
{
    class BasePanel : public Component
    {
    public:
        BasePanel(const std::string& title);
        virtual ~BasePanel() override;

        void render() override = 0;

        const std::string& GetTitle() const { return m_title; }

    protected:
        std::string m_title;
        bool m_isOpen{ true };
    };
}
