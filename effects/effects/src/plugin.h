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

    LilvNode *uri = lilv_new_uri(world, plugin_uri.c_str());

    lilv_world_load_all(world);

    const LilvPlugins *plugins = lilv_world_get_all_plugins(world);
    const LilvPlugin *plugin = lilv_plugins_get_by_uri(plugins, uri);

    const uint32_t n_ports = lilv_plugin_get_num_ports(plugin);

    instance = lilv_plugin_instantiate(plugin, 48000, NULL);

    for (uint32_t p = 0; p < n_ports; ++p) {
      const LilvPort *lport = lilv_plugin_get_port_by_index(plugin, p);

      if (lilv_port_is_a(plugin, lport, lv2_ControlPort)) {
        ctrlbuf.emplace_back(2.0);
        lilv_instance_connect_port(instance, p, &ctrlbuf.back());
      } else if (lilv_port_is_a(plugin, lport, lv2_AudioPort)) {
        if (lilv_port_is_a(plugin, lport, lv2_InputPort)) {
          inbuf.emplace_back(2.2);
          lilv_instance_connect_port(instance, p, &inbuf.back());
        } else if (lilv_port_is_a(plugin, lport, lv2_OutputPort)) {
          outbuf.emplace_back(3.3);
          lilv_instance_connect_port(instance, p, &outbuf.back());
        }
      } else {
        lilv_instance_connect_port(instance, p, nullptr);
      }
    }

    lilv_instance_activate(instance);
  }

  ~Plugin() { lilv_instance_deactivate(instance); }

  void run() {
    lilv_instance_run(instance, 1);
    std::cout << outbuf.back() << std::endl;
  }

  std::vector<float> inbuf = {};
  std::vector<float> outbuf = {};
  std::vector<float> ctrlbuf = {};

  LilvInstance *instance = nullptr;
};

#endif
