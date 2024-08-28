#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/network_settings/NetworkSettingsAddOn.h>
#include <add-ons/network_settings/NetworkSettings.h>
#include <add-ons/network_settings/NetworkProfile.h>

namespace py = pybind11;
using namespace BNetworkKit;

class PyBNetworkConfigurationListener : public BNetworkConfigurationListener{
	public:
        using BNetworkConfigurationListener::BNetworkConfigurationListener;
        void				ConfigurationUpdated(const BMessage& message) override {
        	PYBIND11_OVERLOAD_PURE(void, BNetworkConfigurationListener, ConfigurationUpdated, message);
        }
};

class PyBNetworkSettingsListener : public BNetworkSettingsListener{
	public:
        using BNetworkSettingsListener::BNetworkSettingsListener;
        void				SettingsUpdated(uint32 type) override {
        	PYBIND11_OVERLOAD_PURE(void, BNetworkSettingsListener, SettingsUpdated, type);
        }
};

class PyBNetworkSettingsItem : public BNetworkSettingsItem{
	public:
        using BNetworkSettingsItem::BNetworkSettingsItem;
        BNetworkSettingsType	Type() const override {
        	PYBIND11_OVERLOAD_PURE(BNetworkSettingsType, BNetworkSettingsItem, Type);
        }
		BListItem*			ListItem() override {
			PYBIND11_OVERLOAD_PURE(BListItem*,BNetworkSettingsItem,ListItem);
		}
		BView*				View() override {
			PYBIND11_OVERLOAD_PURE(BView*,BNetworkSettingsItem,View);
		}
		status_t			ProfileChanged(const BNetworkProfile* newProfile) override {
			PYBIND11_OVERLOAD(status_t,BNetworkSettingsItem,ProfileChanged,newProfile);
		}
		status_t			Revert() override {
			PYBIND11_OVERLOAD_PURE(status_t,BNetworkSettingsItem,Revert);
		}
		bool				IsRevertable() override {
			PYBIND11_OVERLOAD_PURE(bool,BNetworkSettingsItem,IsRevertable);
		}
		void				SettingsUpdated(uint32 type) override {
			PYBIND11_OVERLOAD(void,BNetworkSettingsItem,SettingsUpdated,type);
		}
		void				ConfigurationUpdated(const BMessage& message) override {
			PYBIND11_OVERLOAD(void,BNetworkSettingsItem,ConfigurationUpdated,message);
		}
		void				NotifySettingsUpdated() override {
        	PYBIND11_OVERLOAD(void, BNetworkSettingsItem, NotifySettingsUpdated);
        }
};

class PyBNetworkSettingsInterfaceItem : public BNetworkSettingsInterfaceItem{
	public:
        using BNetworkSettingsInterfaceItem::BNetworkSettingsInterfaceItem;
        BNetworkSettingsType	Type() const override {
        	PYBIND11_OVERLOAD_PURE(BNetworkSettingsType, BNetworkSettingsInterfaceItem, Type);
        }
       /* BNetworkSettingsType Type() const override {
        PYBIND11_OVERLOAD_PURE(BNetworkSettingsType, BNetworkSettingsInterfaceItem, Type);
    }*/

    BListItem* ListItem() override {
        PYBIND11_OVERLOAD_PURE(BListItem*, BNetworkSettingsInterfaceItem, ListItem);
    }

    BView* View() override {
        PYBIND11_OVERLOAD_PURE(BView*, BNetworkSettingsInterfaceItem, View);
    }

    status_t Revert() override {
        PYBIND11_OVERLOAD_PURE(status_t, BNetworkSettingsInterfaceItem, Revert);
    }

    bool IsRevertable() override {
        PYBIND11_OVERLOAD_PURE(bool, BNetworkSettingsInterfaceItem, IsRevertable);
    }
	void SettingsUpdated(uint32 type) override {
        PYBIND11_OVERLOAD(void, BNetworkSettingsInterfaceItem, SettingsUpdated, type);
    }

    void ConfigurationUpdated(const BMessage& message) override {
        PYBIND11_OVERLOAD(void, BNetworkSettingsInterfaceItem, ConfigurationUpdated, message);
    }

    void NotifySettingsUpdated() override {
        PYBIND11_OVERLOAD(void, BNetworkSettingsInterfaceItem, NotifySettingsUpdated);
    }
};

class PyBNetworkInterfaceListItem : public BNetworkInterfaceListItem{
	public:
        using BNetworkInterfaceListItem::BNetworkInterfaceListItem;
        void				DrawItem(BView* owner,BRect bounds, bool complete) override {
        	PYBIND11_OVERLOAD(void, BNetworkInterfaceListItem, DrawItem, owner, bounds, complete);
        }
		void				Update(BView* owner, const BFont* font) override {
        	PYBIND11_OVERLOAD(void, BNetworkInterfaceListItem, Update, owner, font);
        }
		void				ConfigurationUpdated(const BMessage& message) override {
        	PYBIND11_OVERLOAD(void, BNetworkInterfaceListItem, ConfigurationUpdated, message);
        }
};

class PyBNetworkSettingsAddOn : public BNetworkSettingsAddOn{
	public:
        using BNetworkSettingsAddOn::BNetworkSettingsAddOn;
        BNetworkSettingsInterfaceItem*		CreateNextInterfaceItem(uint32& cookie,	const char* interface) override {
        	PYBIND11_OVERLOAD(BNetworkSettingsInterfaceItem*, BNetworkSettingsAddOn, CreateNextInterfaceItem, cookie, interface);
        }
		BNetworkSettingsItem*		CreateNextItem(uint32& cookie) override {
        	PYBIND11_OVERLOAD(BNetworkSettingsItem*, BNetworkSettingsAddOn, CreateNextItem, cookie);
        }
};

PYBIND11_MODULE(NetworkSettingsAddOn, m)
{
py::enum_<BNetworkSettingsType>(m, "BNetworkSettingsType", "")
.value("B_NETWORK_SETTINGS_TYPE_INTERFACE", BNetworkSettingsType::B_NETWORK_SETTINGS_TYPE_INTERFACE, "")
.value("B_NETWORK_SETTINGS_TYPE_SERVICE", BNetworkSettingsType::B_NETWORK_SETTINGS_TYPE_SERVICE, "")
.value("B_NETWORK_SETTINGS_TYPE_DIAL_UP", BNetworkSettingsType::B_NETWORK_SETTINGS_TYPE_DIAL_UP, "")
.value("B_NETWORK_SETTINGS_TYPE_VPN", BNetworkSettingsType::B_NETWORK_SETTINGS_TYPE_VPN, "")
.value("B_NETWORK_SETTINGS_TYPE_OTHER", BNetworkSettingsType::B_NETWORK_SETTINGS_TYPE_OTHER, "")
.export_values();

py::class_<BNetworkConfigurationListener,PyBNetworkConfigurationListener>(m, "BNetworkConfigurationListener")
.def("ConfigurationUpdated", &BNetworkConfigurationListener::ConfigurationUpdated, "", py::arg("message"))
;

py::class_<BNetworkSettingsListener,PyBNetworkSettingsListener>(m, "BNetworkSettingsListener")
.def("SettingsUpdated", &BNetworkSettingsListener::SettingsUpdated, "", py::arg("type"))
;

py::class_<BNetworkSettingsItem, PyBNetworkSettingsItem, BNetworkConfigurationListener>(m, "BNetworkSettingsItem")
.def(py::init(), "")
.def("Type", &BNetworkSettingsItem::Type, "")
.def("ListItem", &BNetworkSettingsItem::ListItem, "")
.def("View", &BNetworkSettingsItem::View, "")
.def("ProfileChanged", &BNetworkSettingsItem::ProfileChanged, "", py::arg("newProfile"))
.def("Profile", &BNetworkSettingsItem::Profile, "")
.def("Revert", &BNetworkSettingsItem::Revert, "")
.def("IsRevertable", &BNetworkSettingsItem::IsRevertable, "")
.def("SettingsUpdated", &BNetworkSettingsItem::SettingsUpdated, "", py::arg("type"))
.def("ConfigurationUpdated", &BNetworkSettingsItem::ConfigurationUpdated, "", py::arg("message"))
.def("NotifySettingsUpdated", &BNetworkSettingsItem::NotifySettingsUpdated, "")
;

py::class_<BNetworkSettingsInterfaceItem, PyBNetworkSettingsInterfaceItem, BNetworkSettingsItem>(m, "BNetworkSettingsInterfaceItem")
.def(py::init<const char *>(), "", py::arg("interface"))
.def("Type", &BNetworkSettingsInterfaceItem::Type, "")
.def("Interface", &BNetworkSettingsInterfaceItem::Interface, "")
;

py::class_<BNetworkInterfaceListItem, PyBNetworkInterfaceListItem, BListItem, BNetworkConfigurationListener>(m, "BNetworkInterfaceListItem")
.def(py::init<int, const char *, const char *,BNetworkSettings&>(), "", py::arg("family"), py::arg("interface"), py::arg("label"), py::arg("settings"))
.def("Label", &BNetworkInterfaceListItem::Label, "")
.def("DrawItem", &BNetworkInterfaceListItem::DrawItem, "", py::arg("owner"), py::arg("bounds"), py::arg("complete"))
.def("Update", &BNetworkInterfaceListItem::Update, "", py::arg("owner"), py::arg("font"))
.def("ConfigurationUpdated", &BNetworkInterfaceListItem::ConfigurationUpdated, "", py::arg("message"))
;

py::class_<BNetworkSettingsAddOn>(m, "BNetworkSettingsAddOn")//, PyBNetworkSettingsAddOn>(m, "BNetworkSettingsAddOn")
.def(py::init<image_id,BNetworkSettings&>(), "", py::arg("image"), py::arg("settings"))
.def("CreateNextInterfaceItem", &BNetworkSettingsAddOn::CreateNextInterfaceItem, "", py::arg("cookie"), py::arg("interface"))
.def("CreateNextItem", &BNetworkSettingsAddOn::CreateNextItem, "", py::arg("cookie"))
.def("Image", &BNetworkSettingsAddOn::Image, "")
.def("Resources", &BNetworkSettingsAddOn::Resources, "")
.def("Settings", &BNetworkSettingsAddOn::Settings, "")
;

m.def("instantiate_network_settings_add_on", [](image_id image) {
    BNetworkSettings  settings;
    BNetworkSettingsAddOn * r = instantiate_network_settings_add_on(image, settings);
    return std::make_tuple(r,settings);
}
, "", py::arg("image"));

}
