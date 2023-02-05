mermaid.live

---
title: How to complete a week in CS50x
---
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
flowchart TD
    classDef default fill:whitesmoke, stroke:none
    classDef optional color:crimson,stroke:crimson,stroke-width:.5px;
    classDef required color:blue, stroke:blue,stroke-width:1px;

    Lecture --If more comfortable--> Lab
    Lecture--If less comfortable-->SectionO
    SectionO-->Practice0-->Lab
    Lab --> Pset

subgraph  
Lecture[fa:fa-video Watch Lecture]:::required 
%% SectionO[fa:fa-video Watch Section and any/all Shorts]:::optional
Lab[fa:fa-file-code Submit Lab]:::required
Pset[fa:fa-file-code Submit Problem Set]:::required
%% Practice0(fa:fa-terminal Complete <br> practice problems):::optional
end

subgraph  
    SectionO[fa:fa-video Watch Section and any/all Shorts]:::optional
    Practice0(fa:fa-laptop-code Complete <br> practice problems):::optional

end


