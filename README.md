This is a repository to test Machine Learning models using hls4ml. Some files are for running synthesis and extracting hls report information, while other files are there to help analyze such information.

# Instructions
1. Install `mamba` or `micromamba`. I have [this](https://github.com/Brainz22/useful_notes/blob/main/micromamba.md) instructions I used, but they might work on the computer. If they don't work, maybe use chatGPT to resolve the issue. It is very helpful with things like this.

2. Create the environment using the `environment.yaml` file.

3. After activating your python environment, you run the automated hls4ml tests with
```bash
python3 modelTest.py testConfigs.yaml
```
The directory paths in `modelTest.py` will need to adjusted in order for the code to run without error.

### File Descriptions

* `modelTest.py` takes in the `yaml` file and converts its arguments into a dictionary to access the elements of each key word in the file. It makes random data, defines a model, and trains it. After training the model, the `config` variable is made using the `hls4ml` package. This `config` has the form of a dictionary and we use it to tell the compiler all settings we need to convert our python model to HLS (High Level Synthesis). The last thing is the conditional statements that we use to specify what we want to test from such conversion to HLS. The three options so far are `test = parallelization`, `test = dimensions`, and `test = precision`. When one of these conditions is met, the program `import`s the needed function from the respective file in the folder `util/`. In such functions, the conversion of the python model happens and the results a stored in another dictionary. This dictionary is then `dump`ed into a `json` for easy handling using the `Pandas` package.

* `pdDf.ipynb` is a jupyter notebook showing how I have used the `Pandas` package to analyze data resulting from the python to HLS converion in `modelTest.py`
