

Vector Accelerator Unit for Caravel
====================
Table of contents
=================

   
Overview
========

This repo contains the Vector Accelerator Unit for Caravel, which increases [Caravel](https://github.com/efabless/caravel.git) 
processing capabilities allowing to work with floating point and performs 14 new instructions, 
in addition to parallel processing, this accelerator offers multiplication and division that the 
original RISC-V of Caravel cannot perform. 

The Vector Accelerator Unit was depicted to be combined
with a custom SoC design as the original Caravel template but
with the previous advantages, to achieve this, the accelerator
only uses 18.02% of the User project area, in other words, the end-user has
8.4256 mm2 to implement any custom design.

Like the [Caravel User Project example](https://github.com/efabless/caravel_user_project), this repo explains step-by-step the RTL to GDS workflow with Caravel + Vector Accelerator Unit . 

Prerequisites
=============
- [Caravel](https://github.com/efabless/caravel.git) 


Vector Accelerator Unit Integration
===========

---------------------
Starting your project
---------------------

1. To start the project you first need to create a new repository based on the [Caravel User Project example](https://github.com/efabless/caravel_user_project) template and make sure your repo is public and includes a README.

   *   Follow https://github.com/efabless/caravel_user_project/generate to create a new repository.
   *   Clone the reposity using the following command:
   
      ````
    	git clone <your github repo URL>
      ````
	
#.  To setup your local environment run:

    .. code:: bash
    
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

*   This command will setup your environment by installing the following
    
    - caravel_lite (a lite version of caravel)
    - management core for simulation
    - openlane to harden your design 
    - pdk

	
#.  Now you can start hardening your design

    *   To start hardening you project you need 
        - RTL verilog model for your design for OpenLane to harden
        - A subdirectory for each macro in your project under ``openlane/`` directory, each subdirectory should include openlane configuration files for the macro

        .. code:: bash

           make <module_name>	
        ..

		For an example of hardening a project please refer to `Hardening the User Project using OpenLane`_. .
	
#.  Integrate modules into the user_project_wrapper

    *   Change the environment variables ``VERILOG_FILES_BLACKBOX``, ``EXTRA_LEFS`` and ``EXTRA_GDS_FILES`` in ``openlane/user_project_wrapper/config.tcl`` to point to your module
    *   Instantiate your module(s) in ``verilog/rtl/user_project_wrapper.v``
    *   Harden the user_project_wrapper including your module(s), using this command:

        .. code:: bash

            make user_project_wrapper

#.  Run simulation on your design

    *   You need to include your rtl/gl/gl+sdf files in ``verilog/includes/includes.<rtl/gl/gl+sdf>.caravel_user_project``

        **NOTE:** You shouldn't include the files inside the verilog code

        .. code:: bash

            # you can then run RTL simulations using
            make verify-<testbench-name>-rtl

            # OR GL simulation using
            make verify-<testbench-name>-gl

            # OR for GL+SDF simulation using 
            # sdf annotated simulation is slow
            make verify-<testbench-name>-gl-sdf

            # for example
            make verify-io_ports-rtl

#.  Run opensta on your design

    *   Extract spefs for ``user_project_wrapper`` and macros inside it:

        .. code:: bash

            make extract-parasitics

    *   Create spef mapping file that maps instance names to spef files:

        .. code:: bash

            make create-spef-mapping

    *   Run opensta:

        .. code:: bash

            make caravel-sta

        **NOTE:** To update timing scripts run ``make setup-timing-scripts``
	
#.  Run the precheck locally 

    .. code:: bash

        make precheck
        make run-precheck

#. You are done! now go to https://efabless.com/open_shuttle_program/ to submit your project!
