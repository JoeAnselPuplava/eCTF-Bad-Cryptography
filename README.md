# eCTF-Bad-Cryptography

## Description

This is a lab that shows bad implementations of cryptographic protocols used in the 2025 eCTF. 
The topic of the 2025 eCTF was creating an encoder and decoder for a satellite system.
**DISCLAIMER:** These are real implementations from real schools!

**IMPORTANT**

You are given encrypted frames from channel 1 and 2 (or channel 10008).
However, the provided decoder only has a valid subscription for channel 1!
To get the flag, you must be able to decrypt other channel's frames.
Break every level's designs by exploiting their misuse of cryptographic protocols!


<!-- *Notes to self*
NEED TO CREATE SLIDESHOW FOR EXPLAINING EVERYTHING
I think the lab should be an hour long? Actually let's do 1.25 hours
So presentation should take 10 minutes and then every level will take 10 minutes 
    (50 minutes)
Then presentation explaining how to crack every level and get feedback 
    (15 minutes) -->

## Flag Verfication

Windows

* https://www.shellhacks.com/windows-md5-sha256-checksum-built-in-utility/
* Maybe that?

        echo -n "foobar" | sha256sum

* Maybe this?
    
        certUtil -hashfile C:\file.img SHA256

Mac / Linux

    sha256sum -c Hash

## Level 0

This level is to make sure you're able to compare a hash to a plaintext. 
Like all levels, in the Hash file there's the computed sha256 hash and then to the right of that is the filename to compare this hash to. 
So if you were to try to compare the Hash to the Flag file currently, it should return something like:

    Flag: FAILED
    sha256sum: WARNING: 1 computed checksum did NOT match

Now do the line below and try to compare the hash again:

    echo -n "flag{Harmadillo}" > Flag

It should be returning:

    Flag: OK

**All flags in this lab will be in the format "flag{something_in_here}" with no new line.**


## Prelude 
### Lab setup
I **highly** recommend that you create a virtual environment for Python in the root directory. Python is your friend but installing random directories on your main python is not:

    cd eCTF-Bad-Cryptography
    python -m venv venv

Then activate that virtual environment:

* Windows
        
        # In cmd.exe
        venv\Scripts\activate.bat
        # In PowerShell
        venv\Scripts\Activate.ps1
* Mac/Linux

        source myvenv/bin/activate
Once you're done working in the virtual environment you deactivate it:

    deactivate
### Provided file information
Provided in every level (except level 0) is an 
**encoder.py**, **gen_secrets.py**, **decoder.c**, **decoder.h**, and **decoder.o**.

#### **gen_secrets.py**

gen_secrets.py is used to generate a random key for the system that the encoder and decoder use. 
To generate a secrets file:

    python gen_secrets.py file_name [channels] 
Example:

    python gen_secrets.py secrets 1 2 
From this example you should have a file named *secrets* that you can use with the encoder in the folder!


#### **encoder.py**

encoder.py

First you must install the dependencies for encoder.py.:

    python -m pip install ./tools/

To use the encoder, you need to give it a secrets file generated from the gen_secrets.py provided in the same folder.
The format is:

    python encoder.py secrets_file channel frame_data timestamp

Example:

    python encoder.py secrets 1 "NO FLAG ON THIS CHANNEL" 0



#### **decoder.c** and **h**

decoder.c and decoder.h are provided just so that you can see how the decoder.o is implemented since we don't want security by obscurity! Also, to make these files work without a board, I've taken some creative liberties to adjust them BUT the changes made have no impact on the initial design of the encryption algorithm. 

#### **decoder.o**

**WARNING**: You can probably just object dump this file to get information but I highly recommend **NOT** to do it. The point of this lab is to think of cryptographic vulnerabilities and exploit them.

decoder.o simulates a working decoder that has a valid subscription to channel_1. To use decoder.o you have to give it a file with encrypted frames that are separated by new lines:

In case you have to make it an executable:

    chmod +x decoder.o

To use decoder.o:

    ./decoder.o file_with_encrypted_frames

Example:

    ./decoder.o CHANNEL_1

## Level 1

Just six words for this: wowzer

<details>
<summary> Hint 1 </summary>

What is their encryption algorithm?

</details>

<details>
<summary> Hint 2 </summary>

If you know their key and encryption algorithm, you have everything needed to decrypt any frames!

</details>

## Level 2
Looks more secure than the last one but upon second thought...
<details>
<summary> Hints </summary>
<details>

<summary> Hint 1 </summary>
Same hints as Level 1!
</details>

<details>
<summary> Hint 2 </summary>

Read through [this!](https://cryptography.io/en/latest/hazmat/primitives/symmetric-encryption/)
</details>

</details>

## Level 3
Now it's not so obvious what's wrong, but good understanding of basic cryptography will get you through this!
<details>
<summary> Hints </summary>

<details> 
<summary> Hint 1 </summary>
Why were you give channel 10008 instead of 2?
</details>

<details>
<summary> Hint 2 </summary>
Review ECB encryption!
</details>

<details>
<summary> Hint 3 </summary>
ECB encrypts every block seperately, so try swapping the blocks from the encrypted frames in channel 1 to the encrypted frames in channel 1008
</details>

</details>

</details>

## Level 4
THE FINAL LEVEL! If you've made it this far then you know what to do. Also understanding CBC will be essential for this level!
<details>
<summary> Hints </summary>

<details> 
<summary> Hint 1</summary>

Read through [this!]
(https://cryptography.io/en/latest/hazmat/primitives/symmetric-encryption/)
</details>

<details> 
<summary> Hint 2 </summary>

Read through [this!]
(https://andycaine.com/posts/on-the-importance-of-easy-to-use-cryptography-apis/)
</details>

</details>


## Takeaways

<details>
<summary> Summary </summary>

* **DON'T HARDCODE STUFF!**
* Use authentication to prevent modified frames to be sent
* Using a secure cryptographic system **DOES NOT** mean your system is secure if used improperly




</details>


