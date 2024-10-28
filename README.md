# NuPBO

NuPBO is a local search solver for solving the Pseudo-Boolean Optimization (PBO) problem. 
## Compilation

To compile NuPBO, navigate to the `source_code` directory and run the `make` command.

## Usage

NuPBO requires two mandatory parameters:
- The first parameter is the PBO instance file.
- The second parameter is the seed value.

We utilize runsolver to execute NuPBO. Please refer to `starexec_runsolver.sh` script for more details. This script takes three arguments:
- Argument 1: The PBO instance file. (For information on the opb file format, please refer to the document available at https://www.cril.univ-artois.fr/PB16/format.pdf.)
- Argument 2: Seed value.
- Argument 3: Runtime limit in seconds.

## 
For more details, please refer to the original paper:

[1] Yi Chu, Shaowei Cai, Chuan Luo, Zhendong Lei, Cong Peng: Towards More Efficient Local Search for Pseudo-Boolean Optimization. CP 2023: 12:1-12:18.
