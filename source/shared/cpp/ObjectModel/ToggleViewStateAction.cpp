#include "pch.h"
#include "ParseUtil.h"
#include "ToggleViewStateAction.h"

using namespace AdaptiveSharedNamespace;

ToggleViewStateAction::ToggleViewStateAction() : BaseActionElement(ActionType::ToggleViewState)
{
    PopulateKnownPropertiesSet();
}

std::string ToggleViewStateAction::GetToggleId() const
{
    return m_toggleId;
}

void ToggleViewStateAction::SetToggleId(const std::string& value)
{
    m_toggleId = value;
}

Json::Value ToggleViewStateAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleId)] = GetToggleId();

    return root;
}

std::shared_ptr<BaseActionElement> ToggleViewStateActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<ToggleViewStateAction> toggleViewStateAction = BaseActionElement::Deserialize<ToggleViewStateAction>(json);
    toggleViewStateAction->SetToggleId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ToggleId, true));
    return toggleViewStateAction;
}

std::shared_ptr<BaseActionElement> ToggleViewStateActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ToggleViewStateActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleViewStateAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleId)});
}
