
var controllers = {
    "TestController": {
        "serviceUUID": "19b10000-e8f2-537e-4f6c-d104768a1214",
        "gyroscopeCharacteristicUUID": "19b10001-e8f2-537e-4f6c-d104768a1214",
    }
};

function connect(unityInstance) {
    console.log("Connecting...")
    if ("bluetooth" in navigator) {
        navigator.bluetooth.requestDevice({
            acceptAllDevices: 1,
            optionalServices: ["19b10000-e8f2-537e-4f6c-d104768a1214"]
        }).then((device) => {
            console.log('Connecting to GATT server...');
            return device.gatt.connect();
        }).then((server) => {
            console.log('Getting service...');
            // console.log(server);
            var deviceName = server.device.name;
            unityInstance.SendMessage('Player1', 'EstablishConnection');
            return server.getPrimaryService(controllers[deviceName]["serviceUUID"]);
        }
        ).then((service) => {
            // return { "deviceName": service.device.name, "characteristics": service.getCharacteristics() }
            return service.getCharacteristics();
        }
        ).then((characteristics) => {
            // https://developer.mozilla.org/en-US/docs/Web/API/BluetoothCharacteristicProperties
            console.log('Subscribing...');
            console.log(characteristics);
            for (c in characteristics) {
                console.log(characteristics
                [c].uuid);
                if (characteristics
                [c].uuid == "19b10001-e8f2-537e-4f6c-d104768a1214") {
                    characteristics[c].addEventListener('characteristicvaluechanged', (event) => {
                        unityInstance.SendMessage('Player1', 'UpdateGyroscope');
                    });
                    characteristics[c].startNotifications();
                }
            }
            // ).then((DeviceNameAndCharacteristics) => {
            //     // https://developer.mozilla.org/en-US/docs/Web/API/BluetoothCharacteristicProperties
            //     console.log('Subscribing...');
            //     var deviceName = DeviceNameAndCharacteristics["deviceName"];
            //     var characteristics = DeviceNameAndCharacteristics["characteristics"];
            //     console.log(characteristics);
            //     for (c in characteristics) {
            //         console.log(characteristics
            //         [c].uuid);
            //         if (characteristics
            //         [c].uuid == controllers[deviceName]["gyroscopeCharacteristicUUID"]) {
            //             characteristics[c].addEventListener('characteristicvaluechanged', (event) => {
            //                 console.log("c");
            //                 unityInstance.SendMessage('Player', 'UpdateGyroscope');
            //             });
            //             characteristics[c].startNotifications();
            //         }
            //     }
            console.log("Connected!")
        })
    }
}