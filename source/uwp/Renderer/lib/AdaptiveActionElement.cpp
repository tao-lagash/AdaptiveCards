#include "pch.h"
#include "AdaptiveActionElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveActionElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetTitle(), m_title.GetAddressOf()));

        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));

        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetIconUrl(), m_iconUrl.GetAddressOf()));

        m_isVisible = sharedModel->GetIsVisible();
        m_sentiment = static_cast<ABI::AdaptiveNamespace::Sentiment>(sharedModel->GetSentiment());

        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Title(HSTRING* title) { return m_title.CopyTo(title); }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Title(HSTRING title) { return m_title.Set(title); }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Id(HSTRING* id) { return m_id.CopyTo(id); }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Id(HSTRING id) { return m_id.Set(id); }

    _Use_decl_annotations_ HRESULT AdaptiveActionElementBase::get_IconUrl(HSTRING* iconUrl)
    {
        return m_iconUrl.CopyTo(iconUrl);
    }

    _Use_decl_annotations_ HRESULT AdaptiveActionElementBase::put_IconUrl(HSTRING iconUrl)
    {
        return m_iconUrl.Set(iconUrl);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Sentiment(ABI::AdaptiveNamespace::Sentiment* sentiment)
    {
        *sentiment = m_sentiment;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Sentiment(ABI::AdaptiveNamespace::Sentiment sentiment)
    {
        m_sentiment = sentiment;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_IsVisible(boolean* isVisible)
    {
        *isVisible = m_isVisible;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_IsVisible(boolean isVisible)
    {
        m_isVisible = isVisible;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_ActionTypeString(HSTRING* type) { return m_typeString.CopyTo(type); }

    IFACEMETHODIMP AdaptiveActionElementBase::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveActionElementBase::SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedCardElement)
    {
        sharedCardElement->SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement->SetTitle(HStringToUTF8(m_title.Get()));
        sharedCardElement->SetIconUrl(HStringToUTF8(m_iconUrl.Get()));
        sharedCardElement->SetSentiment(static_cast<AdaptiveSharedNamespace::Sentiment>(m_sentiment));
        sharedCardElement->SetIsVisible(m_isVisible);

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement->SetAdditionalProperties(jsonCpp);
        }

        return S_OK;
    }
}
