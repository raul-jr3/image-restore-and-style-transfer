# image-restore-and-style-transfer
Fast style transfer in tensorflow and some restoration techniques which uses pillow and OpenCV

<b>NOTE : This works only with Python2 </b>

# Installation
Step 1 : Create a new folder and cd into that. <br/>
Step 2 : Create a new virtual environment by running `virtualenv -p python2 <your_env_name>`<br/>
Step 3 : Activate the new environment by running `source <your_env_name>/bin/activate`<br/>
Step 4 : Clone this repository into that environment
Step 5 : run `pip install -r requirements.txt'

# Usage

To try the (basic) image restoration, cd into the image_restore folder <br/>
**Only three modes are available (denoise, unsharp and inpaint)**<br/>
Run `python restore.py --input <path_to_the_input_image> --output <path_to_save_the_output_image> --mode`<br/>
if image inpainting has to be performed then an additional `--mask <path_to_the_mask_image` has to be provided for the mask image<br/>.

To try the image style transfer, cd into the style_transfer folder <br/>
run `python evaluate.py --checkpoint <path_to_the_saved_models> --in-path <path_to_input_image> --out-path <path to output image>`
### the saved models are present in the checkpoint folder.

# Results

### Inpainting

<img src="image_restore/imgs/prez.jpg" width=300 height=300> <img src="image_restore/imgs/mask.jpg" width=300 height=300>

<img src="image_restore/imgs/prez_res.jpg" width=500 height=500>

### Style Transfer

<img src="style_transfer/final_code/input/cap.jpg" width=300 height=300> <img src="style_transfer/final_code/style/wave.jpg" width=300 height=300>

<img src="style_transfer/final_code/output/cap_wave.jpg" width=500 height=500><hr/>

<img src="style_transfer/final_code/input/cap.jpg" width=300 height=300> <img src="style_transfer/final_code/style/the_scream.jpg" width=300 height=300>

<img src="style_transfer/final_code/output/cap_scream.jpg" width=500 height=500>
