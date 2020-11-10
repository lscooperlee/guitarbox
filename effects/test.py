import os
import lilv

os.environ['LV2_PATH'] = '~/tmp/audio/prefix/lib/lv2/'
plugin_uri = 'http://lv2plug.in/plugins/eg-amp'

world=lilv.World()

node=world.new_uri(plugin_uri)
world.load_all()
ps = world.get_all_plugins()

input_node = world.new_uri('http://lv2plug.in/ns/lv2core#InputPort')

# print(ps)
# print(node)

for i in ps:
    # print(i.get_name(), i.get_uri())
    pass

plugin = next((_ for _ in ps if _.get_uri() == plugin_uri))
print(plugin)

for i in range(plugin.get_num_ports()):
    p = plugin.get_port_by_index(i)
    print(p.get_name(), p.get_symbol(), p.get_classes(), p.is_a(input_node))
    print('............')
    for node in p.get_classes():
        print(node)


#p = lilv.Plugin(world, node)

