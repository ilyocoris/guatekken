// https://www.hackster.io/8bitkick/sensor-data-streaming-with-arduino-683a6c
// https://googlechrome.github.io/samples/web-bluetooth/read-characteristic-value-changed-async-await.html
const connectButton = document.getElementById('connectButton');
const controllerServiceUUID = "19b10000-e8f2-537e-4f6c-d104768a1214";
const gyroscopeCharacteristicUUID = "19b10001-e8f2-537e-4f6c-d104768a1214";
var controller;

if ("bluetooth" in navigator)
{
    connectButton.addEventListener('click', function(event) {
        connect();
    });
    // else the browser doesn't support bluetooth
}
else
{
    console.log("browser not supported");
    alert("Error: This browser doesn't support Web Bluetooth. Try using Chrome.");
}

function connect()
{
    console.log("Scan:")
    navigator.bluetooth.requestDevice({
                           // filters: [{
                           //     //services: [ledService]
                           //     name: 'Controller'
                           // }]
                           acceptAllDevices : 1,
                           optionalServices : [ controllerServiceUUID ]
                       })
        .then((device) => {
            controller = device;
            // console.log(controller)
            console.log('Connecting to GATT server...');
            return device.gatt.connect();
        })
        .then(function(server) {
            console.log('Getting service...');
            // console.log(server);
            return server.getPrimaryService(controllerServiceUUID);
        })
        .then(function(service) {
            console.log('Getting characteristics...');
            return service.getCharacteristics();
        })
        .then(function(characteristics) {
            // https://developer.mozilla.org/en-US/docs/Web/API/BluetoothCharacteristicProperties
            console.log('Subscribing...');
            for (c in characteristics)
            {
                if (characteristics
                        [c].uuid == gyroscopeCharacteristicUUID)
                    characteristics[c].addEventListener('characteristicvaluechanged', handleGyroscope);
                else
                    characteristics[c].addEventListener('characteristicvaluechanged', handleData);

                characteristics[c].startNotifications();
            }
            console.log("Connected!")
        })
        .catch(function(error) {
            // catch any errors:
            console.error('Connection failed!', error);
        });
}

function handleData(event)
{
    // unclassified characteristic
    console.log(event);
}

function get_xyz(event)
{
    return {
        // true = byte order from Arduino is littleEndian
        "x" : Math.round(event.target.value.getFloat32(0, true)),
        "y" : Math.round(event.target.value.getFloat32(4, true)),
        "z" :
            Math.round(event.target.value.getFloat32(8, true)),
    };
}

function handleGyroscope(event)
{
    // for gyrposcope characteristic
    // get the xyz data  from the peripheral:
    console.log(get_xyz(event))
    // console.log({
    //     "sensor" : "gyroscope",
    //     "data" : get_xyz(event)
    // });
}
