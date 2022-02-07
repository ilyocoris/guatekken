mergeInto(LibraryManager.library, {
    ConnectToBLE:
        () => {
            var controllers = {
                "TestController": {
                    "serviceUUID": "19b10000-e8f2-537e-4f6c-d104768a1214",
                    "gyroscopeCharacteristicUUID": "19b10001-e8f2-537e-4f6c-d104768a1214",
                }
            }
            if ("bluetooth" in navigator) {
                navigator.bluetooth.requestDevice({
                    // filters: [{
                    //     //services: [ledService]
                    //     name: 'Controller'
                    // }]
                    acceptAllDevices: 1,
                    //optionalServices: [controllerServiceUUID]
                }).then((device) => {
                    controller = device;
                    // console.log(controller)
                    console.log('Connecting to GATT server...');
                    return device.gatt.connect();
                }).then((server) => {
                    console.log('Getting service...');
                    // console.log(server);
                    var deviceName = server.device.name;
                    return server.getPrimaryService(controller[deviceName]["serviceUUID"]);
                }).then((service) => {
                    // https://developer.mozilla.org/en-US/docs/Web/API/BluetoothCharacteristicProperties
                    console.log('Subscribing...');
                    var deviceName = service.device.name;
                    var characteristics = service.getCharacteristics();
                    for (c in characteristics) {
                        if (characteristics
                        [c].uuid == controllers[deviceName]["gyroscopeCharacteristicUUID"]) {
                            console.log(characteristics[c]);
                            characteristics[c].addEventListener('characteristicvaluechanged', handleGyroscope);
                            characteristics[c].startNotifications();
                        }
                    }
                    console.log("Connected!")
                })
            } else {
                return "BLENotAvailable"
            }
        },
});