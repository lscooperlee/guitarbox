#ifndef PLUGIN_H
#define PLUGIN_H

#include <iostream>
#include <string>
#include <vector>

#include <lilv/lilv.h>

struct Plugin {
  Plugin(std::string plugin_uri) {
    LilvWorld *world = lilv_world_new();

    LilvNode *lv2_InputPort = lilv_new_uri(world, LV2_CORE__InputPort);
    LilvNode *lv2_OutputPort = lilv_new_uri(world, LV2_CORE__OutputPort);
    LilvNode *lv2_AudioPort = lilv_new_uri(world, LV2_CORE__AudioPort);
    LilvNode *lv2_ControlPort = lilv_new_uri(world, LV2_CORE__ControlPort);
    LilvNode *lv2_connectionOptional =
        lilv_new_uri(world, LV2_CORE__connectionOptional);
    LilvNode *lv2_default = lilv_new_uri(world, LV2_CORE__default);

    LilvNode *uri = lilv_new_uri(world, plugin_uri.c_str());

    lilv_world_load_all(world);

    const LilvPlugins *plugins = lilv_world_get_all_plugins(world);
    const LilvPlugin *plugin = lilv_plugins_get_by_uri(plugins, uri);

    const uint32_t n_ports = lilv_plugin_get_num_ports(plugin);

    instance = lilv_plugin_instantiate(plugin, 48000, NULL);

    for (uint32_t p = 0; p < n_ports; ++p) {
      const LilvPort *lport = lilv_plugin_get_port_by_index(plugin, p);

      if (lilv_port_is_a(plugin, lport, lv2_ControlPort)) {

        const LilvNode *nm_nd = lilv_port_get_name(plugin, lport);
        const LilvNode *sym_nd = lilv_port_get_symbol(plugin, lport);
        auto idx = lilv_port_get_index(plugin, lport);
        auto def_val = lilv_port_get(plugin, lport, lv2_default);

        std::cout << "Control Port " << lilv_node_as_string(nm_nd) << ", "
                  << lilv_node_as_string(sym_nd) << ", " << idx << ", "
                  << lilv_node_as_float(def_val) << std::endl;

        ctrlbuf.emplace_back(2.0);

        lilv_instance_connect_port(instance, p, &ctrlbuf.back());

        const LilvNode *nm_nd1 = lilv_port_get_name(plugin, lport);
        const LilvNode *sym_nd1 = lilv_port_get_symbol(plugin, lport);
        auto idx1 = lilv_port_get_index(plugin, lport);
        auto def_val1 = lilv_port_get(plugin, lport, lv2_default);

        std::cout << "Control Port " << lilv_node_as_string(nm_nd1) << ", "
                  << lilv_node_as_string(sym_nd1) << ", " << idx1 << ", "
                  << lilv_node_as_float(def_val1) << std::endl;

      } else if (lilv_port_is_a(plugin, lport, lv2_AudioPort)) {
        if (lilv_port_is_a(plugin, lport, lv2_InputPort)) {
          // inbuf.emplace_back(2.2);
          // lilv_instance_connect_port(instance, p, &inbuf.back());
          inbuf.resize(512);
          for (int i = 0; i < 512; ++i) {
            inbuf[i] = 1.2;
          }
          std::cout << "Input Port" << std::endl;
          lilv_instance_connect_port(instance, p, inbuf.data());
        } else if (lilv_port_is_a(plugin, lport, lv2_OutputPort)) {
          // outbuf.emplace_back(3.3);
          // lilv_instance_connect_port(instance, p, &outbuf.back());
          outbuf.resize(512);
          for (int i = 0; i < 512; ++i) {
            outbuf[i] = 3.2;
          }
          std::cout << "Output Port" << std::endl;
          lilv_instance_connect_port(instance, p, outbuf.data());
        }
      } else {
        lilv_instance_connect_port(instance, p, nullptr);
      }
    }

    lilv_instance_activate(instance);
  }

  ~Plugin() { lilv_instance_deactivate(instance); }

  void run(unsigned int nframes) {
    lilv_instance_run(instance, nframes);
    std::cout << nframes << std::endl;
  }

  std::vector<float> inbuf = {};
  std::vector<float> outbuf = {512};
  std::vector<float> ctrlbuf = {512};

  LilvInstance *instance = nullptr;
};

#endif
