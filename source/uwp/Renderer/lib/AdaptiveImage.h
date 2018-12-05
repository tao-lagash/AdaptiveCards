#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Image.h"
#include <windows.foundation.h>
#include "AdaptiveCardElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("c940ac19-5faa-47f3-9d4b-f4d8e7d6ec1d") AdaptiveImage
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveImage,
                                              ABI::AdaptiveNamespace::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveImage);

    public:
        AdaptiveImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Image>& sharedImage);

        // IAdaptiveImage
        IFACEMETHODIMP get_Url(_Out_ HSTRING* uri);
        IFACEMETHODIMP put_Url(_In_ HSTRING uri);

        IFACEMETHODIMP get_BackgroundColor(_Out_ HSTRING* backgroundColor);
        IFACEMETHODIMP put_BackgroundColor(_In_ HSTRING backgroundColor);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ImageStyle* imageStyle);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveNamespace::ImageStyle imageStyle);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::ImageSize* imageSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespace::ImageSize imageSize);

        IFACEMETHODIMP get_PixelWidth(UINT32* Width);
        IFACEMETHODIMP put_PixelWidth(UINT32 Width);

        IFACEMETHODIMP get_PixelHeight(UINT32* Height);
        IFACEMETHODIMP put_PixelHeight(UINT32 Height);

        IFACEMETHODIMP get_AltText(_Out_ HSTRING* text);
        IFACEMETHODIMP put_AltText(_In_ HSTRING text);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HAlignment* hAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveNamespace::HAlignment hAlignment);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing)
        {
            return AdaptiveCardElementBase::get_Spacing(spacing);
        }
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing)
        {
            return AdaptiveCardElementBase::put_Spacing(spacing);
        }

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator)
        {
            return AdaptiveCardElementBase::get_Separator(separator);
        }
        IFACEMETHODIMP put_Separator(_In_ boolean separator)
        {
            return AdaptiveCardElementBase::put_Separator(separator);
        }

        IFACEMETHODIMP get_IsVisible(_Out_ boolean* isVisible)
        {
            return AdaptiveCardElementBase::get_IsVisible(isVisible);
        }
        IFACEMETHODIMP put_IsVisible(_In_ boolean isVisible)
        {
            return AdaptiveCardElementBase::put_IsVisible(isVisible);
        }

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id) { return AdaptiveCardElementBase::get_Id(id); }
        IFACEMETHODIMP put_Id(_In_ HSTRING id) { return AdaptiveCardElementBase::put_Id(id); }

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value)
        {
            return AdaptiveCardElementBase::get_ElementTypeString(value);
        }

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result)
        {
            return AdaptiveCardElementBase::get_AdditionalProperties(result);
        }
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value)
        {
            return AdaptiveCardElementBase::put_AdditionalProperties(value);
        }

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result)
        {
            return AdaptiveCardElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) override;

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveNamespace::HeightType* height)
        {
            return AdaptiveCardElementBase::get_Height(height);
        }
        IFACEMETHODIMP put_Height(_In_ ABI::AdaptiveNamespace::HeightType height)
        {
            return AdaptiveCardElementBase::put_Height(height);
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_url;
        Microsoft::WRL::Wrappers::HString m_backgroundColor;
        ABI::AdaptiveNamespace::ImageStyle m_imageStyle;
        ABI::AdaptiveNamespace::ImageSize m_imageSize;
        Microsoft::WRL::Wrappers::HString m_altText;
        ABI::AdaptiveNamespace::HAlignment m_horizontalAlignment;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;
        UINT32 m_pixelWidth;
        UINT32 m_pixelHeight;
    };

    ActivatableClass(AdaptiveImage);
}
