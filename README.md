

Vector Accelerator Unit for Caravel
====================
   
Overview
========

This repo contains the Vector Accelerator Unit for Caravel, which increases [Caravel](https://github.com/efabless/caravel.git) 
processing capabilities allowing to work with floating point and performs 14 vector
operations, in addition to parallel processing, this accelerator offers multiplication and division that the 
original RISC-V of Caravel cannot perform. 

The Vector Accelerator Unit was depicted to be combined
with a custom SoC design as the original Caravel template but
with the previous advantages, to achieve this, the accelerator
only uses 18.02% of the User project area, in other words, the end-user has
8.4256 $mm^2$ to implement any custom design.

Like the [Caravel User Project example](https://github.com/efabless/caravel_user_project), this repo explains step-by-step the RTL to GDS workflow with Caravel + Vector Accelerator Unit . 

Prerequisites
=============
- Linux

- Python 3.6+ with PIP


Vector Accelerator Unit Integration
===========

---------------------
Starting your project
---------------------

1. To start the project you first need to create a new repository based on the [Caravel User Project example](https://github.com/efabless/caravel_user_project) template and make sure your repo is public and includes a README.

   *   Follow https://github.com/efabless/caravel_user_project/generate to create a new repository.
   *   Clone the reposity using the following command:
   
```` bash
    	git clone <your github repo URL>
````
	
2.  To setup your local environment run:

```` bash
	cd <project_name> # project_name is the name of your repo

	mkdir dependencies

	export OPENLANE_ROOT=$(pwd)/dependencies/openlane_src # you need to export this whenever you start a new shell

	export PDK_ROOT=$(pwd)/dependencies/pdks # you need to export this whenever you start a new shell

	# export the PDK variant depending on your shuttle, if you don't know leave it to the default

	# for sky130 MPW shuttles....
	export PDK=sky130A

	# for the gf180 GFMPW shuttles...
	export PDK=gf180mcuC

	make setup
 ````

*   This command will setup your environment by installing the following
    
    - caravel_lite (a lite version of caravel)
	---
	>By default caravel-lite is installed. To install the full version of caravel, run this prior to calling make install.
	```` bash
		export CARAVEL_LITE=0
	````
    - management core for simulation
    - openlane to harden your design 
    - pdk

	
3.  Now you can start hardening the Vector Accelerator Unit 

    *   To start hardening the Vector Accelerator Unit you need: download the verilog files of the Vector Accelerator Unit, and a subdirectory in your project under ``openlane/`` directory, the subdirectory should include openlane configuration files for the macro.
    	- Vector Accelerator Unit Verilog files
    		- [Top_Module_4_ALU](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/blob/main/verilog/rtl/Top_Module_4_ALU.v)
    		- [ALU files](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/tree/main/verilog/rtl/ALU)
		- [OpenLane subdirectory](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/tree/main/openlane/ALL_ALU)

4. Insie the [ALU.v](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/blob/main/verilog/rtl/ALU/ALU.v) you can choose the instructions you want the Vector Accelerator Unit perform, comment out the unwanted instructions.
	- e.g. To eliminate the division of the Vector Accelerator Unit
```` verilog
	Addition_Subtraction AuI(Add_Sub_A,Add_Sub_B,AddBar_Sub,Add_Sub_Exception,Add_Sub_Output);

	Multiplication MuI(Mul_A,Mul_B,Mul_Exception,Mul_Overflow,Mul_Underflow,Mul_Output);

	//Division DuI(Div_A,Div_B,Div_Exception,Div_Output);

	Floating_Point_to_Integer FuI(Floating_Point,Integer_Value);

````

5. One time the Verilog files are inside ``verilog/rtl`` directory, as equal to [OpenLane files](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/tree/main/openlane/ALL_ALU) are inside ``openlane`` directory, run the following command to harden the Vector Accelerator Unit
       
```` bash
	   make <module_name>	
           #e.g.
	   make ALL_ALU

````
6. Integrate the Vector Accelerator Unit with the user_project_wrapper, to do that instantiate the [Top_Module_4_ALU](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/blob/main/verilog/rtl/Top_Module_4_ALU.v) inside the user_project_wrapper,and modify the user_project_wrapper OpenLane files, see:
	- [User_project_wrapper Verilog files](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/blob/main/verilog/rtl/user_project_wrapper.v)
	- [User_project_wrapper OpenLane files](https://github.com/Baungarten-CINVESTAV/vector_accelerator_unit_for_caravel/tree/main/openlane/user_project_wrapper)

7. Follow [Caravel](https://github.com/efabless/caravel_user_project/blob/main/docs/source/index.rst#section-quickstart)'s workflow to harden your custom modules.
