const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const extend = require('zigbee-herdsman-converters/lib/extend');
const constants = require('zigbee-herdsman-converters/lib/constants');
const types = require('zigbee-herdsman-converters/lib/constants');
const { postfixWithEndpointName, precisionRound } = require('zigbee-herdsman-converters/lib/utils.js') 
const e = exposes.presets;
const ea = exposes.access;

const manufacturerOptions = {
    ynxt : {manufacturerCode: 0xcccc}
}

const fromZigbee_Metering = {
        cluster: 'seMetering',
        type: ['attributeReport', 'readResponse'],
        convert: (model, msg, publish, options, meta) => {
            const payload = {};
            //const multiplier = msg.endpoint.getClusterAttributeValue('seMetering', 'multiplier');
            //const divisor = msg.endpoint.getClusterAttributeValue('seMetering', 'divisor');
            //const factor = multiplier && divisor ? multiplier / divisor : null;

            if (msg.data.hasOwnProperty('currentSummDelivered')) {
                const data = msg.data['currentSummDelivered'];
                const value = (parseInt(data[0]) << 32) + parseInt(data[1]);
                let volume = value * 0.001; //* factor;
				payload[postfixWithEndpointName('volume', msg, model, meta)] = precisionRound(volume, 2);
            } else {
				payload[postfixWithEndpointName('volume', msg, model, meta)] = 0;
			}

            return payload;
        }
    }
	
const toZigbee_Metering = {
        key:['volume'],
        convertGet: async (entity, key, meta) => {
			await entity.read('seMetering', ['currentSummDelivered']);
		},
		convertSet: async (entity, key, value, meta) => {
			return null;
		}
    }
	
const fromZigbee_msFlowMeasurement = {
        cluster: 'msFlowMeasurement',
        type: ['attributeReport', 'readResponse'],
        convert: (model, msg, publish, options, meta) => {
			const result = {};
			if(msg.data.hasOwnProperty('measuredValue')) {
				result[postfixWithEndpointName('flow', msg, model, meta)] = msg.data['measuredValue'] / 10;
			} else {
				result[postfixWithEndpointName('flow', msg, model, meta)] = 0;
			}
			return result;
		}
    }

const toZigbee_msFlowMeasurement = {
        key:['flow'],
        convertGet: async (entity, key, meta) => {
			await entity.read('msFlowMeasurement', ['measuredValue']);
		},
		convertSet: async (entity, key, value, meta) => {
			return null;
		}
    }
	
const toZigbee_deviceEnabled = {
        key:['enabled'],
        convertGet: async (entity, key, meta) => {
			await entity.read('genBasic', ['deviceEnabled']);
		},
		convertSet: async (entity, key, value, meta) => {
			const payload = {0x0012: {value: value == 'Enabled' ? 0x01 : 0x00 , type: 0x10}};
			await entity.write('genBasic', payload);
			return  {state: {[key]: value}};
		}
    }
	
const fromZigbee_deviceEnabled = {
        cluster: 'genBasic',
        type: ['readResponse'],
        convert: (model, msg, publish, options, meta) => {
			const result = {};
			if(msg.data.hasOwnProperty('deviceEnabled')) {
				result[postfixWithEndpointName('enabled', msg, model, meta)] = msg.data['deviceEnabled'] == 0x01 ? 'Enabled' : 'Disabled';
			}
			return result;
		}
    }

const definition = {
    zigbeeModel: ['WM-01'],
    model: 'WM-01',
    vendor: 'YNXT',
    description: 'Water meter',
    fromZigbee: [fromZigbee_deviceEnabled, fromZigbee_msFlowMeasurement, fromZigbee_Metering, fz.on_off],
	toZigbee: [toZigbee_deviceEnabled, toZigbee_msFlowMeasurement, toZigbee_Metering, tz.currentsummdelivered, tz.factory_reset, tz.on_off],
    meta: {
        multiEndpoint: true
    },
    endpoint: (device) => {
        return {
            'l1': 1,
			'l2': 2,
			'l3': 3,
			'l4': 4
        };
    },
    configure: async (device, coordinatorEndpoint, logger) => {
		const firstEndpoint = device.getEndpoint(1);
        await firstEndpoint.bind('msFlowMeasurement', constants.defaultBindGroup);
        await reporting.bind(firstEndpoint, coordinatorEndpoint, ['msFlowMeasurement']);
		await firstEndpoint.read('msFlowMeasurement', ['measuredValue']);
		await firstEndpoint.read('genBasic', ['deviceEnabled']);
		
		await firstEndpoint.bind('seMetering', constants.defaultBindGroup);
		await firstEndpoint.read('seMetering', ['currentSummDelivered']);
		await reporting.currentSummDelivered(firstEndpoint, {min: 60, change: 1.0});
		
		const secondEndpoint = device.getEndpoint(2);
		await secondEndpoint.bind('msFlowMeasurement', constants.defaultBindGroup);
        await reporting.bind(secondEndpoint, coordinatorEndpoint, ['msFlowMeasurement']);
		await secondEndpoint.read('msFlowMeasurement', ['measuredValue']);
		await secondEndpoint.read('genBasic', ['deviceEnabled']);
		
		await secondEndpoint.bind('seMetering', constants.defaultBindGroup);
		await secondEndpoint.read('seMetering', ['currentSummDelivered']);
		await reporting.currentSummDelivered(secondEndpoint, {min: 60, change: 1.0});
		
		const thirdEndpoint = device.getEndpoint(3);
		await thirdEndpoint.bind('msFlowMeasurement', constants.defaultBindGroup);
        await reporting.bind(thirdEndpoint, coordinatorEndpoint, ['msFlowMeasurement']);
		await thirdEndpoint.read('msFlowMeasurement', ['measuredValue']);
		await thirdEndpoint.read('genBasic', ['deviceEnabled']);
		
		await thirdEndpoint.bind('seMetering', constants.defaultBindGroup);
		await thirdEndpoint.read('seMetering', ['currentSummDelivered']);
		await reporting.currentSummDelivered(thirdEndpoint, {min: 60, change: 1.0});
		
		const fourthEndpoint = device.getEndpoint(4);
		await fourthEndpoint.read('genOnOff', ['onOff']);
    },
	exposes: [
		exposes.enum('enabled', ea.SET, ['Enabled', 'Disabled']).withDescription('Device enabled').withEndpoint('l1'),
		exposes.numeric('flow', ea.STATE).withUnit('L/min').withDescription('Flow').withEndpoint('l1'),
		exposes.numeric('volume', ea.STATE_GET).withUnit('Liters').withDescription('Volume').withEndpoint('l1'),
		exposes.enum('reset', ea.SET, ['Reset']).withDescription('Reset volume after change filter').withEndpoint('l1'),
		
		exposes.enum('enabled', ea.SET, ['Enabled', 'Disabled']).withDescription('Device enabled').withEndpoint('l2'),
		exposes.numeric('flow', ea.STATE).withUnit('L/min').withDescription('Flow').withEndpoint('l2'),
		exposes.numeric('volume', ea.STATE_GET).withUnit('Liters').withDescription('Volume').withEndpoint('l2'),
		exposes.enum('reset', ea.SET, ['Reset']).withDescription('Reset volume after change filter').withEndpoint('l2'),
		
		exposes.enum('enabled', ea.SET, ['Enabled', 'Disabled']).withDescription('Device enabled').withEndpoint('l3'),
		exposes.numeric('flow', ea.STATE).withUnit('L/min').withDescription('Flow').withEndpoint('l3'),
		exposes.numeric('volume', ea.STATE_GET).withUnit('Liters').withDescription('Volume').withEndpoint('l3'),
		exposes.enum('reset', ea.SET, ['Reset']).withDescription('Reset volume after change filter').withEndpoint('l3'),
		
		exposes.enum('reset', ea.SET, ['Reset']).withDescription('Reset whole device collected volume').withEndpoint('l4'),
		e.switch().withDescription('External load').withEndpoint('l4')
	]
};

module.exports = definition;