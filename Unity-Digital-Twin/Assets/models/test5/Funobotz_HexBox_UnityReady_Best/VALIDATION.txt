FUNOBOTZ Hex Box - Best Unity-Ready Version

This package is prepared for reliable Unity import.

WHAT WAS IMPROVED
- Corrected non-mirrored logo orientation on side faces
- Centered pivot/origin for each object
- Root-level logo texture added for more reliable Unity material pickup
- FBX and OBJ now reference a visible logo texture file: funobotz_wordmark_whitebg.png
- Units are in meters for Unity (11 cm inner diameter, 7 cm base height, 2 cm lid height)

FILES
- Funobotz_HexBase.fbx / .obj
- Funobotz_HexLid.fbx / .obj
- Funobotz_HexBox_Combined.fbx / .obj
- funobotz_wordmark_whitebg.png (root-level for automatic Unity detection)
- Textures/ folder also included

UNITY NOTES
1. Put the whole extracted folder inside Assets.
2. If Unity asks to extract materials, keep them in the same folder.
3. Combined model pivot is at the center of the full assembled box.
4. Base pivot is at the center of the base object.
5. Lid pivot is at the center of the lid object.
6. To place the separate lid on the separate base in the seated position, a good starting localPosition for the lid is approximately (0, 0.06025, 0) relative to the base center.

DIMENSIONS
- Base inner diameter (flat-to-flat): 0.11 m
- Base height: 0.07 m
- Lid height: 0.02 m
- Sides: 6

VALIDATION
Funobotz_HexBase: bounds min [-0.06611238 -0.035      -0.05748   ], max [0.06611238 0.035      0.05748   ], center [0. 0. 0.]
Funobotz_HexLid: bounds min [-0.06928781 -0.01025    -0.06023   ], max [0.06928781 0.01025    0.06023   ], center [0. 0. 0.]
Funobotz_HexBox_Combined: bounds min [-0.06928781 -0.03525    -0.06023   ], max [0.06928781 0.03525    0.06023   ], center [0. 0. 0.]
