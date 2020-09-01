---
title: Donate
narrow: true
permalink: list/donate.html
show_profile: true
---

{% for project in site.projects %}
- [{{ project.title }}]({{ site.baseurl }}{{ project.url }})
{% endfor %}
