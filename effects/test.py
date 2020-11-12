import os
import lilv
import numpy as np

#os.environ['LV2_PATH'] = '~/tmp/audio/prefix/lib/lv2/'
plugin_uri = 'http://lv2plug.in/plugins/eg-amp'

world=lilv.World()

node=world.new_uri(plugin_uri)
world.load_all()
ps = world.get_all_plugins()

input_port_node = world.new_uri('http://lv2plug.in/ns/lv2core#InputPort')
output_port_node = world.new_uri('http://lv2plug.in/ns/lv2core#OutputPort')
audio_port_node = world.new_uri('http://lv2plug.in/ns/lv2core#AudioPort')
control_port_node = world.new_uri('http://lv2plug.in/ns/lv2core#ControlPort')
connection_optional_port_node = world.new_uri('http://lv2plug.in/ns/lv2core#connectionOptional')

# print(ps)
# print(node)

for i in ps:
    # print(i.get_name(), i.get_uri())
    pass

plugin = next((_ for _ in ps if _.get_uri() == plugin_uri))
print(plugin)

inst = lilv.Instance(plugin, 48000)
print(inst)

in_buf = []
out_buf = []
ctrl_buf = []
for i in range(plugin.get_num_ports()):
    p = plugin.get_port_by_index(i)

    print(p.get_name(), p.get_symbol(), p.get_classes())

    # print('............')
    # for node in p.get_classes():
        # print(node)


    if p.is_a(control_port_node):
        ctrl_buf.append(np.array([2]))
        inst.connect_port(i, ctrl_buf[-1])

    elif p.is_a(audio_port_node):

        if p.is_a(input_port_node):
            in_buf.append(np.array([1]))
            inst.connect_port(i, in_buf[-1])
        elif p.is_a(output_port_node):
            out_buf.append(np.array([0.0]))
            inst.connect_port(i, out_buf[-1])

#print(in_buf, out_buf, ctrl_buf)

inst.activate()

while True:
    #read to in_buf
    #in_buf[0] = 1
    inst.run(1)
    #write from out_buf
    print(out_buf)



#p = lilv.Plugin(world, node)

