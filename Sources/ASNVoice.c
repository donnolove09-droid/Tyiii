#include "ASNVoice.h"

const char *ASNVoiceVersion(void) { return "0.2.0-ai-integration-starter"; }

const char *ASNVoiceModelStatus(ASNVoicePreset preset) {
    switch (preset) {
        case ASNVoicePresetMale1: return "MODEL_NOT_INSTALLED:male_1";
        case ASNVoicePresetMale2: return "MODEL_NOT_INSTALLED:male_2";
        case ASNVoicePresetFemale: return "MODEL_NOT_INSTALLED:female_1";
        default: return "UNSUPPORTED_PRESET";
    }
}

/* Fail closed: never pretend a pitch-shift is neural voice conversion.
   Replace this function with the validated Core ML/runtime adapter only after
   compatible trained model artifacts are available. */
int32_t ASNVoiceProcessFloat(float *pcm, uint32_t frames, uint32_t channels,
                             ASNVoicePreset preset, float strength) {
    (void)strength;
    if (!pcm || frames == 0 || (channels != 1 && channels != 2))
        return ASN_VOICE_INVALID_ARGUMENT;
    if (preset < ASNVoicePresetMale1 || preset > ASNVoicePresetFemale)
        return ASN_VOICE_INVALID_ARGUMENT;
    return ASN_VOICE_MODEL_NOT_INSTALLED;
}
