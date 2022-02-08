
var controllers = {
    "TestController": {
        "serviceUUID": "19b10000-e8f2-537e-4f6c-d104768a1214",
        "gyroscopeCharacteristicUUID": "19b10001-e8f2-537e-4f6c-d104768a1214",
    }
};

function get_xyz(event) {
    return {
        // true = byte order from Arduino is littleEndian
        "x": event.target.value.getFloat32(0, true),
        "y": event.target.value.getFloat32(4, true),
        "z": event.target.value.getFloat32(8, true),
    };
}

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
            unityInstance.SendMessage('Player1', 'EstablishConnection', deviceName);
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
                        xyz_json = get_xyz(event);
                        unityInstance.SendMessage('Player1', 'UpdateGyroscope', JSON.stringify(xyz_json));
                    });
                    characteristics[c].startNotifications();
                }
            }
            console.log("Connected!")
        })
    }
}