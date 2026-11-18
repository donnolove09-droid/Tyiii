# Model artifacts (not included)

Place only models you have permission to use here.

Expected future layout:
```text
Models/
  male_1/
    voice_conversion.mlmodelc/
    model.json
  male_2/
    voice_conversion.mlmodelc/
    model.json
  female_1/
    voice_conversion.mlmodelc/
    model.json
```

A valid Core ML package must be produced from a supported, documented model architecture. An RVC `.pth` checkpoint or `.index` file is **not** a Core ML model and cannot simply be renamed. The adapter must be implemented against the actual model input/output tensor shapes and tested with reference audio before enabling live processing.
