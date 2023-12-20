---
title: How to complete a week in CS50x 2024
---

%%{ init: { 'graph': { 'curve': 'stepAfter' } } }%%
flowchart TD
    classDef default fill:whitesmoke, stroke:none
    classDef optional color:crimson,stroke:crimson,stroke-width:.1px;
    classDef required color:blue, stroke:blue,stroke-width:1px,fill:white;

    Lecture-->SectionO
    SectionO-->Shorts
    Shorts -->Pset
    Pset ~~~ Practice0


subgraph  
Lecture[fa:fa-video Watch Lecture]:::required 
SectionO[fa:fa-video Watch Section]:::required
Shorts[fa:fa-video Watch any/all Shorts <br> for more in depth study fa:fa-question-circle]:::optional
Pset[fa:fa-file-code Submit Problem Set]:::required
Practice0["fa:fa-user-check Want more practice? <br> Optionally, complete Practice problems <br> before or after the Problem Set"]:::optional
end
