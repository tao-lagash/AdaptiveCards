#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    enum VisibilityToggle
    {
        IsVisible_Toggle,
        IsVisible_True,
        IsVisible_False,
    };

    class ToggleVisibilityTargetElement 
    {
    public:
        ToggleVisibilityTargetElement();

        std::string GetTargetId() const;
        void SetTargetId(const std::string& value);

        VisibilityToggle GetVisibilityToggle() const;
        void SetVisibilityToggle(VisibilityToggle value);

        std::string Serialize();
        Json::Value SerializeToJsonValue();

        static std::shared_ptr<ToggleVisibilityTargetElement> Deserialize(ParseContext& context, const Json::Value& root);
        static std::shared_ptr<ToggleVisibilityTargetElement> DeserializeFromString(ParseContext& context,
                                                                                    const std::string& jsonString);

    private:
        std::string m_targetId;
        VisibilityToggle m_visibilityToggle;
    };
}
