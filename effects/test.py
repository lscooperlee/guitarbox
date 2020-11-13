import ctypes
import os
import lilv
import numpy as np

os.environ['LV2_PATH'] = '~/tmp/lilv/install/lib/lv2/'
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

# in_buf = []
# out_buf = []
# ctrl_buf = []

ctrlf=np.array([3.2], dtype=np.float32)
inf=np.array([1.2], dtype=np.float32)
outf=np.array([2.3], dtype=np.float32)

for i in range(plugin.get_num_ports()):
    p = plugin.get_port_by_index(i)

    print(i, p.get_name(), p.get_symbol(), p.get_classes())

    # print('............')
    # for node in p.get_classes():
        # print(node)

    if p.is_a(control_port_node):
#        ctrl_buf.append(np.array([10.0]))
  #      inst.connect_port(i, ctrl_buf[-1])
        inst.connect_port(i, ctrlf)

    elif p.is_a(audio_port_node):

        if p.is_a(input_port_node):
#            in_buf.append(np.array([3]))
#            inst.connect_port(i, in_buf[-1])
            inst.connect_port(i, inf)
        elif p.is_a(output_port_node):
#            out_buf.append(np.array([2]))
#            inst.connect_port(i, out_buf[-1])
            inst.connect_port(i, outf)

    else:
        print('unkown type')
        for node in p.get_classes():
            print(node)


inst.activate()


for i in range(3):
    inf[0]=i #read to in_buf

    inst.run(1)
    #write from out_buf
#    print(ctrl_buf, ctrlf, in_buf, out_buf)
    print(ctrlf, inf, outf)



#p = lilv.Plugin(world, node)

