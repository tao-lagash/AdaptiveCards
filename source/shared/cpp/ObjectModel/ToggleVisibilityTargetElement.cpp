#include "pch.h"
#include "ParseUtil.h"
#include "ToggleVisibilityTargetElement.h"

using namespace AdaptiveSharedNamespace;

ToggleVisibilityTargetElement::ToggleVisibilityTargetElement() : m_visibilityToggle(IsVisible_Toggle)
{
}

std::string ToggleVisibilityTargetElement::GetTargetId() const
{
    return m_targetId;
}

void ToggleVisibilityTargetElement::SetTargetId(const std::string& value)
{
    m_targetId = value;
}

VisibilityToggle ToggleVisibilityTargetElement::GetVisibilityToggle() const
{
    return m_visibilityToggle;
}

void ToggleVisibilityTargetElement::SetVisibilityToggle(VisibilityToggle value)
{
    m_visibilityToggle = value;
}

std::shared_ptr<ToggleVisibilityTargetElement> ToggleVisibilityTargetElement::Deserialize(ParseContext&, const Json::Value& json)
{
    auto toggleVisibilityTargetElement = std::make_shared<ToggleVisibilityTargetElement>();

    if (json.isString())
    {
        toggleVisibilityTargetElement->SetTargetId(json.asString());
    }
    else
    {
        toggleVisibilityTargetElement->SetTargetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ElementId, true));

        auto propertyValue = json.get(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible), Json::Value());
        if (!propertyValue.empty())
        {
            if (!propertyValue.isBool())
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                 "Value for property " +
                                                     AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible) +
                                                     " was invalid. Expected type bool.");
            }

            toggleVisibilityTargetElement->SetVisibilityToggle(propertyValue.asBool() ? IsVisible_True : IsVisible_False);
        }
    }

    return toggleVisibilityTargetElement;
}

std::shared_ptr<ToggleVisibilityTargetElement> ToggleVisibilityTargetElement::DeserializeFromString(ParseContext& context,
                                                                                                    const std::string& jsonString)
{
    return ToggleVisibilityTargetElement::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ToggleVisibilityTargetElement::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ToggleVisibilityTargetElement::SerializeToJsonValue()
{
    auto visibilityToggle = GetVisibilityToggle();

    if (visibilityToggle == IsVisible_Toggle)
    {
        // If this is a toggle target, return just a json string
        return Json::Value(GetTargetId());
    }
    else
    {
        // For true and false targets return a json object with a "targetId" and "isVisisble" properties
        Json::Value root;
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ElementId)] = GetTargetId();
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible)] = (visibilityToggle == IsVisible_True);
        return root;
    }
}
