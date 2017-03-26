# FindEliza
Find Eliza in a scene using Feature Descriptors and Homography

Premise:
This is a small project that detects Eliza Thornberry (from The Wild ThornBerrys) in a given scene.
It utilizes the OpenCV3 library for Feature Detection, Homography and Perspective Tranform.

The code contains explanatory comments to follow the technical details.

Inspiration:
While researching OpenCV3 libs and what I can do as a simple first step, I thought of Eliza.
(I used to be a child voice-over artist for Eliza for the Hindi translation).
I decided to have some fun and revisit memories while building this.

How to Run:
./FindEliza <QueryImg> <SceneImg>
Some sample images are included with this project.
Suggestion: ./FindEliza images/query/Eliza.png images/scene/TWTB2.jpg

Next Steps:
1. The project has very basic error handling and no logging. Including these would be necessary if the scope
   is increased.
2. To make the detection more robust, a training mechanism like HaarCascade can be utilized.
3. The classes in the project can be abstracted out further, there is scope of design improvement.

Key Learnings:
1. OpenCV is extensive and powerful!
2. It is very easy to over-engineer with the amount of libraries available.
   This makes it essential to keep the scope in check.
3. There is no one mantra, trial and error, with iterative development, is key to getting desired results.
