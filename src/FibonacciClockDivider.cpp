#include <stdint.h>
#include "SynthKit.hpp"
#include "../deps/SynthDevKit/src/FibonacciClock.hpp"

struct FibonacciClockDividerModule : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		TOP_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		FIRST_OUTPUT,
		SECOND_OUTPUT,
		THIRD_OUTPUT,
		FOURTH_OUTPUT,
		FIFTH_OUTPUT,
		SIXTH_OUTPUT,
		SEVENTH_OUTPUT,
		EIGHTH_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
    FIRST_LED,
    SECOND_LED,
    THIRD_LED,
    FOURTH_LED,
    FIFTH_LED,
    SIXTH_LED,
    SEVENTH_LED,
    EIGHTH_LED,
		NUM_LIGHTS
	};

	FibonacciClockDividerModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
    clock = new SynthDevKit::FibonacciClock(8, 1.7f);
  }

	void step() override;

  SynthDevKit::FibonacciClock *clock;
};


void FibonacciClockDividerModule::step() {
	float in = inputs[TOP_INPUT].value;
  bool *states = clock->update(in);

	for (int i = 0; i < 8; i++) {
		if (states[i] == true) {
			outputs[i].value = in;
			lights[i].value = 1.0f;
		} else {
			outputs[i].value = 0;
			lights[i].value = 0;
		}
	}
}


struct FibonacciClockDividerWidget : ModuleWidget {
	FibonacciClockDividerWidget(FibonacciClockDividerModule *module);
};

FibonacciClockDividerWidget::FibonacciClockDividerWidget(FibonacciClockDividerModule *module) : ModuleWidget(module) {
	box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/FibonacciClockDivider.svg")));
		addChild(panel);
	}

	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addInput(Port::create<PJ301MPort>(Vec(10, 34), Port::INPUT, module, FibonacciClockDividerModule::TOP_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 73), Port::OUTPUT, module, FibonacciClockDividerModule::FIRST_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 108), Port::OUTPUT, module, FibonacciClockDividerModule::SECOND_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 143), Port::OUTPUT, module, FibonacciClockDividerModule::THIRD_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 178), Port::OUTPUT, module, FibonacciClockDividerModule::FOURTH_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 213), Port::OUTPUT, module, FibonacciClockDividerModule::FIFTH_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 248), Port::OUTPUT, module, FibonacciClockDividerModule::SIXTH_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 283), Port::OUTPUT, module, FibonacciClockDividerModule::SEVENTH_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(10, 318), Port::OUTPUT, module, FibonacciClockDividerModule::EIGHTH_OUTPUT));

  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 81), module, FibonacciClockDividerModule::FIRST_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 116), module, FibonacciClockDividerModule::SECOND_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 151), module, FibonacciClockDividerModule::THIRD_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 186), module, FibonacciClockDividerModule::FOURTH_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 221), module, FibonacciClockDividerModule::FIFTH_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 256), module, FibonacciClockDividerModule::SIXTH_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 291), module, FibonacciClockDividerModule::SEVENTH_LED));
  addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(35, 326), module, FibonacciClockDividerModule::EIGHTH_LED));
}

Model *modelFibonacciClockDivider = Model::create<FibonacciClockDividerModule, FibonacciClockDividerWidget>("SynthKit", "Fibonacci Clock Divider", "Fibonacci Clock Divider", UTILITY_TAG, CLOCK_TAG);
