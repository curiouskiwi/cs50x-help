mermaid.live

---
title: How to complete a week in CS50x 2024
---
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
flowchart TD
    classDef default fill:whitesmoke, stroke:none
    classDef optional color:crimson,stroke:crimson,stroke-width:.5px;
    classDef required color:blue, stroke:blue,stroke-width:1px;

    Lecture-->SectionO
    SectionO-->Pset
    Pset--Want some extra problems?-->Practice0

subgraph  
Lecture[fa:fa-video Watch Lecture]:::required 
SectionO[fa:fa-video Watch Section <br> and optionally Shorts]:::optional
Pset[fa:fa-file-code Submit Problem Set]:::required
Practice0(fa:fa-terminal Complete <br> practice problems):::optional
end
