#include "pch.h"
#include "AdaptiveToggleTarget.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "ToggleVisibilityTargetElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleTarget::RuntimeClassInitialize() noexcept try
    {
        RuntimeClassInitialize(std::make_shared<ToggleVisibilityTargetElement>());
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleTarget::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTargetElement>& sharedToggleTarget)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleTarget->GetTargetId(), m_id.GetAddressOf()));
        m_visibilityToggle = (ABI::AdaptiveNamespace::VisibilityToggle) sharedToggleTarget->GetVisibilityToggle();
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleTarget::get_Id(HSTRING* title) { return m_id.CopyTo(title); }

    _Use_decl_annotations_ HRESULT AdaptiveToggleTarget::put_Id(HSTRING title) { return m_id.Set(title); }

    _Use_decl_annotations_ HRESULT AdaptiveToggleTarget::get_VisibilityToggle(ABI::AdaptiveNamespace::VisibilityToggle* value)
    {
        *value = m_visibilityToggle;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleTarget::put_VisibilityToggle(ABI::AdaptiveNamespace::VisibilityToggle value)
    {
        m_visibilityToggle = value;
        return S_OK;
    }

    HRESULT AdaptiveToggleTarget::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTargetElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTargetElement> toggleTarget =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityTargetElement>();

        std::string id;
        RETURN_IF_FAILED(HStringToUTF8(m_id.Get(), id));
        toggleTarget->SetTargetId(id);
        toggleTarget->SetVisibilityToggle((AdaptiveSharedNamespace::VisibilityToggle) m_visibilityToggle);

        sharedModel = toggleTarget;
        return S_OK;
    }
    CATCH_RETURN;
}
