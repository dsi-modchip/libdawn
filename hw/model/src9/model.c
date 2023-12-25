
#include <dawn/hw/model.h>


extern enum dawn_hw_model_type __dawn_hw_model_type; /** set by crt0 */
enum dawn_hw_model_type __dawn_hw_model_type;

enum dawn_hw_model_type dawn_hw_model_get(void) {
	return __dawn_hw_model_type;
}

