module;

#include "ksmaxis/ksmaxis.hpp"

export module ksmaxis;

export namespace ksmaxis {
    using ksmaxis::InputMode;
    using ksmaxis::DeviceFlags;
    using ksmaxis::AxisValues;
    using ksmaxis::Init;
    using ksmaxis::Terminate;
    using ksmaxis::IsInitialized;
    using ksmaxis::Update;
    using ksmaxis::GetAxisDeltas;
    using ksmaxis::GetRequiredDeviceFlags;

    using ksmaxis::operator|;
    using ksmaxis::operator&;
    using ksmaxis::operator~;
    using ksmaxis::operator|=;
    using ksmaxis::operator&=;
}