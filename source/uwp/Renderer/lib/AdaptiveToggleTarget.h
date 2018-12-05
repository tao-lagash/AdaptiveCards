#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ToggleVisibilityTargetElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveToggleTarget
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveToggleTarget,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveToggleTarget);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTargetElement>& sharedToggleTarget);

        // IAdaptiveToggleTarget
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_VisibilityToggle(ABI::AdaptiveNamespace::VisibilityToggle* value);
        IFACEMETHODIMP put_VisibilityToggle(ABI::AdaptiveNamespace::VisibilityToggle value);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTargetElement>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::VisibilityToggle m_visibilityToggle;
    };

    ActivatableClass(AdaptiveToggleTarget);
}
