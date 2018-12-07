#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include <windows.foundation.h>
#include "Enums.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("CDCCC115-7C53-4A04-9F5B-754BBC00C80E") AdaptiveActionElementBase : public IUnknown
    {
    protected:
        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel);

        IFACEMETHODIMP get_ActionTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_IconUrl(_Out_ HSTRING* iconUrl);
        IFACEMETHODIMP put_IconUrl(_In_ HSTRING iconUrl);

        IFACEMETHODIMP get_Sentiment(_Out_ ABI::AdaptiveNamespace::Sentiment *sentiment);
        IFACEMETHODIMP put_Sentiment(_In_ ABI::AdaptiveNamespace::Sentiment sentiment);

        IFACEMETHODIMP get_IsVisible(boolean* separator);
        IFACEMETHODIMP put_IsVisible(boolean separator);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedCardElement);

        virtual HRESULT GetSharedModel(std::shared_ptr<BaseActionElement>& sharedModel) = 0;

    private:
        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::Wrappers::HString m_iconUrl;
        ABI::AdaptiveNamespace::Sentiment m_sentiment;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
        Microsoft::WRL::Wrappers::HString m_typeString;
        boolean m_isVisible;
    };
}
