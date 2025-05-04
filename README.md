# RTD Custom module design rationale 
## Contents
1. Introduction 
2. Hardware design choices
3. Software design choices

## Introduction
Temperature measurement is a common operation in many industries. There are multiple ways to collect and record temperature measurements in a digital format. One such way is to use RTD sensors. 

### What is an RTD?
An RTD is a resistance temperature detector. It's resistance changes as the ambient temperature changes. The relationship between the resistance and the temperature is approximately "linear". It offers the best linear response of any temperature sensor.

They are built to standadized curves and tolerances, The most common one is the DIN curve. The DIN curve is defined by the following equation:
$$R_{RTD} = R_0(1 + \alpha T)$$
Where $R_{RTD}$ is the resistance of the RTD, $R_0$ is the resistance at 0°C, and $\alpha$ is the temperature coefficient. The temperature coefficient is  the change in resistance per degree Celsius. The temperature coefficient is typically 0.00385 for the DIN curve.
