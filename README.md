# BrunesCharacterSystem-UE4Plugin
A character system from simple saving and loading to dynamic narrative death and life of a character. This system supports multiplayer or single player character life.

### Usage

BruCharacterSpawner can be placed in the world. You will need to create a new blueprint class from UBruCharacterData and fill it out with an actor that inherits the CharacterDataInterface. Next your game mode will need the Character Manager Interface. Your game mode should spawn the character manager in the method: OnConstruction.

Theory: This character manager will now track characters throughout the game. The spawners will choose to spawn them when those levels are loaded or reloaded. This is for unique enemies not spawned groups... for now.


### Commit Guide

Follow https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/ and https://github.com/Allar/ue4-style-guide

### License

BSD 2-Clause License

Copyright (c) 2017, Michael Brune
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
