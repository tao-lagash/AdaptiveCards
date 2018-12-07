
#include "pch.h"
#include "BaseActionElement.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

BaseActionElement::BaseActionElement(ActionType type) :
    m_type(type), m_typeString(ActionTypeToString(type)), m_sentiment(Sentiment::Default), m_isVisible(true)
{
    PopulateKnownPropertiesSet();
}

std::string BaseActionElement::GetElementTypeString() const
{
    return m_typeString;
}

void BaseActionElement::SetElementTypeString(const std::string& value)
{
    m_typeString = value;
}

std::string BaseActionElement::GetTitle() const
{
    return m_title;
}

void BaseActionElement::SetTitle(const std::string& value)
{
    m_title = value;
}

std::string BaseActionElement::GetId() const
{
    return m_id;
}

void BaseActionElement::SetId(const std::string& value)
{
    m_id = value;
}

std::string BaseActionElement::GetIconUrl() const
{
    return m_iconUrl;
}

void BaseActionElement::SetIconUrl(const std::string& value)
{
    m_iconUrl = value;
}

Sentiment BaseActionElement::GetSentiment() const
{
    return m_sentiment;
}

void BaseActionElement::SetSentiment(const Sentiment& value)
{
    m_sentiment = value;
}

bool BaseActionElement::GetIsVisible() const
{
    return m_isVisible;
}

void BaseActionElement::SetIsVisible(const bool value)
{
    m_isVisible = value;
}

const ActionType BaseActionElement::GetElementType() const
{
    return m_type;
}

std::string BaseActionElement::Serialize() const
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value BaseActionElement::SerializeToJsonValue() const
{
    Json::Value root = GetAdditionalProperties();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = ActionTypeToString(m_type);
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = m_id;

    if (!m_title.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = m_title;
    }

    if (m_sentiment != Sentiment::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sentiment)] = SentimentToString(m_sentiment);
    }

    if (!m_iconUrl.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl)] = m_iconUrl;
    }

    if (!m_isVisible)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible)] = false;
    }

    return root;
}

Json::Value BaseActionElement::GetAdditionalProperties() const
{
    return m_additionalProperties;
}

void BaseActionElement::SetAdditionalProperties(Json::Value const& value)
{
    m_additionalProperties = value;
}

void BaseActionElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sentiment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible)});
}

void BaseActionElement::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    if (!m_iconUrl.empty())
    {
        RemoteResourceInformation imageResourceInfo;
        imageResourceInfo.url = m_iconUrl;
        imageResourceInfo.mimeType = "image";
        resourceInfo.push_back(imageResourceInfo);
    }
}
