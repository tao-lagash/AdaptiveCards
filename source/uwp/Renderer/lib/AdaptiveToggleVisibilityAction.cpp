#include "pch.h"
#include "AdaptiveToggleVisibilityAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleVisibility::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityAction>();
        return RuntimeClassInitialize(toggleVisibilityAction);
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibility::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction>& sharedToggleVisibilityAction) try
    {
        if (sharedToggleVisibilityAction == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedToggleVisibilityAction->GetTargetElements(), m_toggleId.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedToggleVisibilityAction));
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibility::get_ActionType(ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::ToggleVisibility;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibility::get_TargetElements(HSTRING* toggleId)
    {
        return m_toggleId.CopyTo(toggleId);
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibility::put_TargetElements(HSTRING toggleId)
    {
        return m_toggleId.Set(toggleId);
    }

    HRESULT AdaptiveToggleVisibility::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(toggleVisibilityAction)));

        std::string toggleId;
        RETURN_IF_FAILED(HStringToUTF8(m_toggleId.Get(), toggleId));
        toggleVisibilityAction->SetTargetElements(toggleId);

        sharedModel = toggleVisibilityAction;
        return S_OK;
    }
    CATCH_RETURN;
}
