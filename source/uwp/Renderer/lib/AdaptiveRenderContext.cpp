#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveError.h"
#include "AdaptiveWarning.h"
#include "InputValue.h"
#include "Util.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRenderContext::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveRenderContext::RuntimeClassInitialize(IAdaptiveHostConfig* hostConfig,
                                                          IAdaptiveElementRendererRegistration* elementRendererRegistration,
                                                          IAdaptiveCardResourceResolvers* resourceResolvers,
                                                          IResourceDictionary* overrideDictionary,
                                                          IResourceDictionary* defaultActionSentimentStyles,
                                                          RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_hostConfig = hostConfig;
        m_elementRendererRegistration = elementRendererRegistration;
        m_renderResult = renderResult;
        m_resourceResolvers = resourceResolvers;
        m_overrideDictionary = overrideDictionary;
        m_actionSentimentDefaultDictionary = defaultActionSentimentStyles;

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionInvoker>(&m_actionInvoker, renderResult));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveMediaEventInvoker>(&m_mediaEventInvoker, renderResult));

        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_HostConfig(IAdaptiveHostConfig** value)
    {
        return m_hostConfig.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_ElementRenderers(IAdaptiveElementRendererRegistration** value)
    {
        return m_elementRendererRegistration.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_ActionInvoker(IAdaptiveActionInvoker** value)
    {
        return m_actionInvoker.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_MediaEventInvoker(IAdaptiveMediaEventInvoker** value)
    {
        return m_mediaEventInvoker.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_ResourceResolvers(IAdaptiveCardResourceResolvers** value)
    {
        return m_resourceResolvers.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::get_OverrideStyles(_COM_Outptr_ IResourceDictionary** overrideDictionary)
    {
        return m_overrideDictionary.CopyTo(overrideDictionary);
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::AddError(ABI::AdaptiveNamespace::ErrorStatusCode statusCode, HSTRING message)
    {
        ComPtr<AdaptiveError> error;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveError>(&error, statusCode, message));
        ComPtr<IVector<ABI::AdaptiveNamespace::IAdaptiveError*>> errors;
        RETURN_IF_FAILED(m_renderResult->get_Errors(&errors));
        return (errors->Append(error.Detach()));
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::AddWarning(ABI::AdaptiveNamespace::WarningStatusCode statusCode, HSTRING message)
    {
        ComPtr<AdaptiveWarning> warning;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveWarning>(&warning, statusCode, message));
        ComPtr<IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>> warnings;
        RETURN_IF_FAILED(m_renderResult->get_Warnings(&warnings));
        return (warnings->Append(warning.Detach()));
    }

    HRESULT AdaptiveRenderContext::get_CardFrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** value)
    {
        return m_cardFrameworkElement.CopyTo(value);
    }

    HRESULT AdaptiveRenderContext::put_CardFrameworkElement(ABI::Windows::UI::Xaml::IFrameworkElement* value)
    {
        m_cardFrameworkElement = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderContext::AddAnimationTimeline(HSTRING targetName, ABI::Windows::UI::Xaml::Media::Animation::ITimeline* timeline)
    {
        m_animationTimelines[HStringToUTF8(targetName)] = timeline;
        return S_OK;
    }

    HRESULT AdaptiveRenderContext::GetAnimationTimline(HSTRING targetName, ABI::Windows::UI::Xaml::Media::Animation::ITimeline** timeline)
    {
        m_animationTimelines[HStringToUTF8(targetName)].CopyTo(timeline);
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveRenderContext::AddInputValue(IAdaptiveInputValue* inputValue)
    {
        return m_renderResult->AddInputValue(inputValue);
    }

    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> AdaptiveRenderContext::GetDefaultActionSentimentDictionary()
    {
        return m_actionSentimentDefaultDictionary;
    }
}
