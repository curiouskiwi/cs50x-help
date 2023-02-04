mermaid.live

---
title: How to complete a week in CS50x
---
flowchart TD
    classDef default fill:whitesmoke
    classDef optional color:crimson,stroke:#eee,stroke-width:.5px;
    classDef required color:blue, stroke:#eee,stroke-width:1px;

    Lecture --more comfortable--> Lab
    Lecture--less comfortable?-->SectionO
    SectionO-->Practice0-->Lab
    Lab --> Pset

subgraph  
Lecture[fa:fa-video Watch Lecture]:::required 
SectionO[fa:fa-video Watch Section and any/all Shorts]:::optional
Lab[fa:fa-file-code Submit Lab]:::required
Pset[fa:fa-file-code Submit Problem Set]:::required
Practice0(fa:fa-terminal Complete <br> practice problems):::optional
end
