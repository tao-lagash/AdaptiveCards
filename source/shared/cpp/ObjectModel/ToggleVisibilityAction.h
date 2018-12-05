#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class ToggleVisibilityAction : public BaseActionElement
    {
    public:
        ToggleVisibilityAction();

        std::string GetTargetElements() const;
        void SetTargetElements(const std::string& value);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_toggleId;
    };

    class ToggleVisibilityParser : public ActionElementParser
    {
    public:
        ToggleVisibilityParser() = default;
        ToggleVisibilityParser(const ToggleVisibilityParser&) = default;
        ToggleVisibilityParser(ToggleVisibilityParser&&) = default;
        ToggleVisibilityParser& operator=(const ToggleVisibilityParser&) = default;
        ToggleVisibilityParser& operator=(ToggleVisibilityParser&&) = default;
        virtual ~ToggleVisibilityParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;

        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString);
    };
}
