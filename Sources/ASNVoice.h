#ifndef ASNVoice_h
#define ASNVoice_h
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ASNVoicePresetMale1 = 0,
    ASNVoicePresetMale2 = 1,
    ASNVoicePresetFemale = 2
} ASNVoicePreset;

typedef enum {
    ASN_VOICE_OK = 0,
    ASN_VOICE_INVALID_ARGUMENT = -1,
    ASN_VOICE_MODEL_NOT_INSTALLED = -10,
    ASN_VOICE_MODEL_UNSUPPORTED = -11
} ASNVoiceStatus;

/* No neural conversion until a compatible model runtime is integrated. */
int32_t ASNVoiceProcessFloat(float *pcm, uint32_t frames, uint32_t channels,
                             ASNVoicePreset preset, float strength);
const char *ASNVoiceVersion(void);
const char *ASNVoiceModelStatus(ASNVoicePreset preset);

#ifdef __cplusplus
}
#endif
#endif
