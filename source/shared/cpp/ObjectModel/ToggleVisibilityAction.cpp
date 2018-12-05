#include "pch.h"
#include "ParseUtil.h"
#include "ToggleVisibilityAction.h"

using namespace AdaptiveSharedNamespace;

ToggleVisibilityAction::ToggleVisibilityAction() : BaseActionElement(ActionType::ToggleVisibility)
{
    PopulateKnownPropertiesSet();
}

std::string ToggleVisibilityAction::GetTargetElements() const
{
    return m_toggleId;
}

void ToggleVisibilityAction::SetTargetElements(const std::string& value)
{
    m_toggleId = value;
}

Json::Value ToggleVisibilityAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TargetElements)] = GetTargetElements();

    return root;
}

std::shared_ptr<BaseActionElement> ToggleVisibilityParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<ToggleVisibilityAction> toggleVisibilityAction = BaseActionElement::Deserialize<ToggleVisibilityAction>(json);
    toggleVisibilityAction->SetTargetElements(ParseUtil::GetString(json, AdaptiveCardSchemaKey::TargetElements, true));
    return toggleVisibilityAction;
}

std::shared_ptr<BaseActionElement> ToggleVisibilityParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ToggleVisibilityParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleVisibilityAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TargetElements)});
}
