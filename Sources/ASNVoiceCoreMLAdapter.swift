import Foundation
import CoreML

/// Integration boundary only. A trained, compatible Core ML model is required.
/// RVC .pth/.index files cannot be loaded directly by this class.
@available(iOS 15.0, *)
final class ASNVoiceCoreMLAdapter {
    enum AdapterError: Error {
        case modelNotInstalled(String)
        case unsupportedModelContract
    }

    func loadModel(named modelID: String) throws -> MLModel {
        let bundle = Bundle.main
        guard let url = bundle.url(forResource: modelID, withExtension: "mlmodelc") else {
            throw AdapterError.modelNotInstalled(modelID)
        }
        let configuration = MLModelConfiguration()
        configuration.computeUnits = .all
        let model = try MLModel(contentsOf: url, configuration: configuration)

        // Check the model contract before implementing real-time prediction.
        guard !model.modelDescription.inputDescriptionsByName.isEmpty,
              !model.modelDescription.outputDescriptionsByName.isEmpty else {
            throw AdapterError.unsupportedModelContract
        }
        return model
    }
}
