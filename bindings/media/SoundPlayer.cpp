#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/SoundPlayer.h>
#include <media/Sound.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(SoundPlayer, m)
{
//m.attr("SoundPlayNode") = py::cast(SoundPlayNode);

/*py::class_<sound_error, std::exception>(m, "sound_error")
.def(py::init<const char *>(), "", py::arg("string"))
.def("what", &sound_error::what, "")
;*/

py::register_exception<sound_error>(m, "sound_error");
class sound_error : public std::exception {
	public:
	explicit sound_error(const char* msg) : message(msg) {}
	const char* what() const noexcept override { 
		return message;
	}
	private: const char* message;
};
/* In python you can write: except sound_player.sound_error as e: print(f"Caught sound_error: {e.what()}")*/

py::enum_<BSoundPlayer::sound_player_notification>(m, "sound_player_notification", "")
.value("B_STARTED", BSoundPlayer::sound_player_notification::B_STARTED, "")
.value("B_STOPPED", BSoundPlayer::sound_player_notification::B_STOPPED, "")
.value("B_SOUND_DONE", BSoundPlayer::sound_player_notification::B_SOUND_DONE, "")
.export_values();

py::class_<BSoundPlayer>(m, "BSoundPlayer")
//.def(py::init<const char *, BufferPlayerFunc, EventNotifierFunc, void *>(), "", py::arg("name")=NULL, py::arg("playerFunction")=NULL, py::arg("eventNotifierFunction")=NULL, py::arg("cookie")=NULL)
//.def(py::init<const media_raw_audio_format *, const char *, BufferPlayerFunc, EventNotifierFunc, void *>(), "", py::arg("format"), py::arg("name")=NULL, py::arg("playerFunction")=NULL, py::arg("eventNotifierFunction")=NULL, py::arg("cookie")=NULL)
//.def(py::init<const media_node &, const media_multi_audio_format *, const char *, const media_input *, BufferPlayerFunc, EventNotifierFunc, void *>(), "", py::arg("toNode"), py::arg("format")=NULL, py::arg("name")=NULL, py::arg("input")=NULL, py::arg("playerFunction")=NULL, py::arg("eventNotifierFunction")=NULL, py::arg("cookie")=NULL)

.def(py::init<const char*, BSoundPlayer::BufferPlayerFunc, BSoundPlayer::EventNotifierFunc, void*>(), py::arg("name") = nullptr, py::arg("playerFunction") = nullptr, py::arg("eventNotifierFunction") = nullptr, py::arg("cookie") = nullptr)
.def(py::init<const media_raw_audio_format*, const char*, BSoundPlayer::BufferPlayerFunc, BSoundPlayer::EventNotifierFunc, void*>(), py::arg("format"), py::arg("name") = nullptr, py::arg("playerFunction") = nullptr, py::arg("eventNotifierFunction") = nullptr, py::arg("cookie") = nullptr)
.def(py::init<const media_node&, const media_multi_audio_format*, const char*, const media_input*, BSoundPlayer::BufferPlayerFunc, BSoundPlayer::EventNotifierFunc, void*>(), py::arg("toNode"), py::arg("format") = nullptr, py::arg("name") = nullptr, py::arg("input") = nullptr, py::arg("playerFunction") = nullptr, py::arg("eventNotifierFunction") = nullptr, py::arg("cookie") = nullptr)

.def("InitCheck", &BSoundPlayer::InitCheck, "")
.def("Format", &BSoundPlayer::Format, "")
.def("Start", &BSoundPlayer::Start, "")
.def("Stop", &BSoundPlayer::Stop, "", py::arg("block")=true, py::arg("flush")=true)
//.def("BufferPlayer", &BSoundPlayer::BufferPlayer, "")
//attempt1
//.def("BufferPlayer", [](const BSoundPlayer& self) { return self.BufferPlayer(); },"")
//attempt2
.def("BufferPlayer", [](const BSoundPlayer& self) -> std::function<void(void*, void*, size_t, const media_raw_audio_format&)> { 
	BSoundPlayer::BufferPlayerFunc playerFunc = self.BufferPlayer();
	return [playerFunc](void* cookie, void* buffer, size_t size, const media_raw_audio_format& format) { if (playerFunc) { playerFunc(cookie, buffer, size, format); } }; },"") //TODO test this
.def("SetBufferPlayer", &BSoundPlayer::SetBufferPlayer, "", py::arg(""))
//.def("EventNotifier", &BSoundPlayer::EventNotifier, "")
//attempt variadic impossible
/*.def("EventNotifier", [](const BSoundPlayer& self) -> std::function<void(void*, BSoundPlayer::sound_player_notification, ...)> { 
	BSoundPlayer::EventNotifierFunc notifierFunc = self.EventNotifier();
	return [notifierFunc](void* cookie, BSoundPlayer::sound_player_notification what, ...) { if (notifierFunc) { notifierFunc(cookie, what); } }; },"")*/
.def("EventNotifier", [](const BSoundPlayer& self) -> std::function<void(void*, BSoundPlayer::sound_player_notification)> { 
	BSoundPlayer::EventNotifierFunc notifierFunc = self.EventNotifier();
	return [notifierFunc](void* cookie, BSoundPlayer::sound_player_notification what) { if (notifierFunc) { notifierFunc(cookie, what); } }; },"") //TODO test this
.def("SetNotifier", &BSoundPlayer::SetNotifier, "", py::arg("eventNotifierFunction"))
.def("Cookie", &BSoundPlayer::Cookie, "")
.def("SetCookie", &BSoundPlayer::SetCookie, "", py::arg("cookie"))
.def("SetCallbacks", &BSoundPlayer::SetCallbacks, "", py::arg("playerFunction")=NULL, py::arg("eventNotifierFunction")=NULL, py::arg("cookie")=NULL)
.def("CurrentTime", &BSoundPlayer::CurrentTime, "")
.def("PerformanceTime", &BSoundPlayer::PerformanceTime, "")
.def("Preroll", &BSoundPlayer::Preroll, "")
.def("StartPlaying", py::overload_cast<BSound *, bigtime_t>(&BSoundPlayer::StartPlaying), "", py::arg("sound"), py::arg("atTime")=0)
.def("StartPlaying", py::overload_cast<BSound *, bigtime_t, float>(&BSoundPlayer::StartPlaying), "", py::arg("sound"), py::arg("atTime"), py::arg("withVolume"))
.def("SetSoundVolume", &BSoundPlayer::SetSoundVolume, "", py::arg("sound"), py::arg("newVolume"))
.def("IsPlaying", &BSoundPlayer::IsPlaying, "", py::arg("id"))
.def("StopPlaying", &BSoundPlayer::StopPlaying, "", py::arg("id"))
.def("WaitForSound", &BSoundPlayer::WaitForSound, "", py::arg("id"))
.def("Volume", &BSoundPlayer::Volume, "")
.def("SetVolume", &BSoundPlayer::SetVolume, "", py::arg("volume"))
.def("VolumeDB", &BSoundPlayer::VolumeDB, "", py::arg("forcePoll")=false)
.def("SetVolumeDB", &BSoundPlayer::SetVolumeDB, "", py::arg("dB"))
.def("GetVolumeInfo", &BSoundPlayer::GetVolumeInfo, "", py::arg("_node"), py::arg("_parameterID"), py::arg("_minDB"), py::arg("_maxDB"))
.def("Latency", &BSoundPlayer::Latency, "")
.def("HasData", &BSoundPlayer::HasData, "")
.def("SetHasData", &BSoundPlayer::SetHasData, "", py::arg("hasData"))
;
/*
py::class_<playing_sound>(m, "playing_sound")
.def_readwrite("next", &playing_sound::next, "")
.def_readwrite("current_offset", &playing_sound::current_offset, "")
.def_readwrite("sound", &playing_sound::sound, "")
.def_readwrite("id", &playing_sound::id, "")
.def_readwrite("delta", &playing_sound::delta, "")
.def_readwrite("rate", &playing_sound::rate, "")
.def_readwrite("wait_sem", &playing_sound::wait_sem, "")
.def_readwrite("volume", &playing_sound::volume, "")
;

py::class_<waiting_sound>(m, "waiting_sound")
.def_readwrite("next", &waiting_sound::next, "")
.def_readwrite("start_time", &waiting_sound::start_time, "")
.def_readwrite("sound", &waiting_sound::sound, "")
.def_readwrite("id", &waiting_sound::id, "")
.def_readwrite("rate", &waiting_sound::rate, "")
.def_readwrite("volume", &waiting_sound::volume, "")
;*/


}
