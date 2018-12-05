#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"
#include "ToggleVisibilityTargetElement.h"

namespace AdaptiveSharedNamespace
{
    class ToggleVisibilityAction : public BaseActionElement
    {
        friend class ToggleVisibilityParser;

    public:
        ToggleVisibilityAction();

        const std::vector<std::shared_ptr<ToggleVisibilityTargetElement>>& GetTargetElements() const;
        std::vector<std::shared_ptr<ToggleVisibilityTargetElement>>& GetTargetElements();

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet() override;

        std::vector<std::shared_ptr<ToggleVisibilityTargetElement>> m_targetElements;
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
