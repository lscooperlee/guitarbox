#include "lv2/core/lv2.h"

/** Include standard C headers */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define DISTORTION_URI "https://github.com/lscooperlee/guitarbox"

typedef struct {
	// Port buffers
	const float* ctrl;
	const float* input;
	float*       output;
} Distortor;

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
	Distortor* distortor = (Distortor*)calloc(1, sizeof(Distortor));

	return (LV2_Handle)distortor;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
	Distortor* distortor = (Distortor*)instance;

	switch (port) {
	case 0:
		distortor->input = (const float*)data;
		break;
	case 1:
		distortor->output = (float*)data;
		break;
	case 2:
		distortor->ctrl = (const float*)data;
		break;
	}
}

static void
activate(LV2_Handle instance)
{
}

static void
run(LV2_Handle instance, uint32_t n_sdistortorles)
{
	const Distortor* distortor = (const Distortor*)instance;

    const float        ctrl = *(distortor->ctrl);
    const float* const input  = distortor->input;
    float* const       output = distortor->output;

    for (uint32_t pos = 0; pos < n_sdistortorles; pos++) {
        auto out = input[pos];

        if (input[pos] > ctrl){
            out = ctrl;
        }else if(input[pos] < -ctrl){
            out = -ctrl;
        }

        output[pos] = out;
    }
}

static void
deactivate(LV2_Handle instance)
{
}

static void
cleanup(LV2_Handle instance)
{
	free(instance);
}

static const void*
extension_data(const char* uri)
{
	return NULL;
}

static const LV2_Descriptor descriptor = {
	DISTORTION_URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	cleanup,
	extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
	return index == 0 ? &descriptor : NULL;
}
