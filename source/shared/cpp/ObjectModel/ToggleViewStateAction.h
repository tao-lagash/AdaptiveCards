#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class ToggleViewStateAction : public BaseActionElement
    {
    public:
        ToggleViewStateAction();

        std::string GetToggleId() const;
        void SetToggleId(const std::string& value);

        Json::Value SerializeToJsonValue() const override;

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_toggleId;
    };

    class ToggleViewStateActionParser : public ActionElementParser
    {
    public:
        ToggleViewStateActionParser() = default;
        ToggleViewStateActionParser(const ToggleViewStateActionParser&) = default;
        ToggleViewStateActionParser(ToggleViewStateActionParser&&) = default;
        ToggleViewStateActionParser& operator=(const ToggleViewStateActionParser&) = default;
        ToggleViewStateActionParser& operator=(ToggleViewStateActionParser&&) = default;
        virtual ~ToggleViewStateActionParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;

        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString);
    };
}
