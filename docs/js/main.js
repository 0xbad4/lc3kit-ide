(function () {
  "use strict";

  var cfg = window.SITE_CONFIG;
  var repoUrl = "https://github.com/" + cfg.repo;

  function $(selector, root) {
    return (root || document).querySelector(selector);
  }

  function el(tag, props, children) {
    var node = document.createElement(tag);
    Object.keys(props || {}).forEach(function (key) {
      if (key === "text") node.textContent = props[key];
      else if (key === "class") node.className = props[key];
      else node.setAttribute(key, props[key]);
    });
    (children || []).forEach(function (child) {
      node.appendChild(child);
    });
    return node;
  }

  function formatSize(bytes) {
    if (bytes >= 1048576) return (bytes / 1048576).toFixed(1) + " MB";
    if (bytes >= 1024) return Math.round(bytes / 1024) + " KB";
    return bytes + " B";
  }

  function formatDate(iso) {
    var date = new Date(iso);
    if (isNaN(date)) return "";
    return date.toLocaleDateString(undefined, { year: "numeric", month: "short", day: "numeric" });
  }

  function detectPlatform() {
    var ua = (navigator.userAgentData && navigator.userAgentData.platform) || navigator.platform || navigator.userAgent || "";
    if (/win/i.test(ua)) return "windows";
    if (/mac|iphone|ipad/i.test(ua)) return "macos";
    if (/linux|x11|cros/i.test(ua)) return "linux";
    return null;
  }

  function platformOf(name) {
    var keys = Object.keys(cfg.platforms);
    for (var i = 0; i < keys.length; i++) {
      if (cfg.platforms[keys[i]].match.test(name)) return keys[i];
    }
    return null;
  }

  function setupLinks() {
    var map = {
      "[data-repo-link]": repoUrl,
      "[data-releases-link]": repoUrl + "/releases",
      "[data-issues-link]": repoUrl + "/issues",
      "[data-core-link]": "https://github.com/" + cfg.coreRepo,
      "[data-changelog-link]": repoUrl + "/blob/main/CHANGELOG.md",
      "[data-core-docs]": cfg.coreDocs
    };
    Object.keys(map).forEach(function (selector) {
      document.querySelectorAll(selector).forEach(function (a) {
        a.href = map[selector];
        if (map[selector].indexOf("http") === 0) {
          a.target = "_blank";
          a.rel = "noopener";
        }
      });
    });
    $("#footerText").textContent = cfg.name + " is open source under the " + cfg.license + " licence. Developed by a student for students.";
  }

  function setupInstitutions() {
    var list = $("#instList");
    cfg.institutions.forEach(function (inst) {
      var left = el("div", {}, [
        el("div", { class: "inst-name", text: inst.name }),
        el("div", { class: "inst-course", text: inst.course })
      ]);
      var link = el("a", { href: inst.url, target: "_blank", rel: "noopener", text: "Course page" });
      list.appendChild(el("li", {}, [left, link]));
    });
  }

  function setupNav() {
    var toggle = $("#navToggle");
    var nav = $("#nav");
    toggle.addEventListener("click", function () {
      var open = nav.classList.toggle("open");
      toggle.setAttribute("aria-expanded", String(open));
    });
    nav.addEventListener("click", function (event) {
      if (event.target.tagName === "A") {
        nav.classList.remove("open");
        toggle.setAttribute("aria-expanded", "false");
      }
    });
  }

  function setupTour() {
    var tabs = $("#tourTabs");
    var img = $("#tourImg");
    var caption = $("#tourCaption");
    var buttons = [];

    function select(index) {
      var panel = cfg.panels[index];
      buttons.forEach(function (button, i) {
        button.setAttribute("aria-selected", String(i === index));
        button.tabIndex = i === index ? 0 : -1;
      });
      img.src = panel.image;
      img.alt = panel.title + " panel";
      caption.textContent = "";
      caption.appendChild(el("strong", { text: panel.title }));
      caption.appendChild(document.createTextNode(panel.text));
    }

    cfg.panels.forEach(function (panel, index) {
      var button = el("button", { type: "button", role: "tab", text: panel.title });
      button.addEventListener("click", function () { select(index); });
      button.addEventListener("keydown", function (event) {
        var next = null;
        if (event.key === "ArrowDown" || event.key === "ArrowRight") next = (index + 1) % buttons.length;
        if (event.key === "ArrowUp" || event.key === "ArrowLeft") next = (index - 1 + buttons.length) % buttons.length;
        if (next !== null) {
          event.preventDefault();
          select(next);
          buttons[next].focus();
        }
      });
      buttons.push(button);
      tabs.appendChild(button);
    });

    select(0);
  }

  function setupBuild() {
    var code = $("#buildCode");
    cfg.buildSteps.forEach(function (line) {
      code.appendChild(el("span", { class: "prompt", text: "$ " }));
      code.appendChild(document.createTextNode(line + "\n"));
    });

    var button = $("#copyBuild");
    button.addEventListener("click", function () {
      var text = cfg.buildSteps.join("\n");
      var done = function () {
        button.textContent = "Copied";
        setTimeout(function () { button.textContent = "Copy"; }, 1600);
      };
      if (navigator.clipboard && navigator.clipboard.writeText) {
        navigator.clipboard.writeText(text).then(done, function () { });
      }
    });
  }

  function renderEmpty(card, message) {
    card.textContent = "";
    card.appendChild(el("h3", { text: "Latest release" }));
    var box = el("div", { class: "empty-state" });
    box.appendChild(el("p", { text: message }));
    box.appendChild(el("p", { text: "Packages will be listed here when a release is available. Until then, the project can be built from source using the steps beside this card." }));
    card.appendChild(box);
    var actions = el("div", { class: "primary-dl" });
    var link = el("a", { class: "btn btn-primary", href: repoUrl + "/releases", target: "_blank", rel: "noopener", text: "Open the releases page" });
    actions.appendChild(el("p", {}));
    actions.appendChild(link);
    card.appendChild(actions);
  }

  function renderRelease(card, release) {
    var assets = (release.assets || []).filter(function (asset) {
      return !/\.(sha256|sig|asc|txt)$/i.test(asset.name);
    });

    card.textContent = "";
    card.appendChild(el("h3", { text: "Latest release" }));

    var meta = el("div", { class: "release-meta" });
    meta.appendChild(el("span", { class: "tag", text: release.tag_name }));
    if (release.published_at) meta.appendChild(el("span", { text: formatDate(release.published_at) }));
    meta.appendChild(el("a", { href: release.html_url, target: "_blank", rel: "noopener", text: "Release notes" }));
    card.appendChild(meta);

    if (!assets.length) {
      var none = el("div", { class: "empty-state" });
      none.appendChild(el("p", { text: "This release has no packaged files attached." }));
      none.appendChild(el("p", { text: "Source archives are available on the release page." }));
      card.appendChild(none);
      return;
    }

    var detected = detectPlatform();
    var preferred = assets.filter(function (asset) { return platformOf(asset.name) === detected; })[0] || assets[0];
    var preferredPlatform = platformOf(preferred.name);
    var label = preferredPlatform ? "Download for " + cfg.platforms[preferredPlatform].label : "Download";

    var primary = el("div", { class: "primary-dl" });
    primary.appendChild(el("a", { class: "btn btn-primary", href: preferred.browser_download_url, text: label }));
    primary.appendChild(el("span", { class: "status", text: preferred.name + " (" + formatSize(preferred.size) + ")" }));
    card.appendChild(primary);

    var list = el("ul", { class: "asset-list" });
    assets.forEach(function (asset) {
      var platform = platformOf(asset.name);
      var item = el("li", {}, [
        el("span", { class: "plat", text: platform ? cfg.platforms[platform].label : "Other" }),
        el("a", { href: asset.browser_download_url, text: asset.name }),
        el("span", { class: "size", text: formatSize(asset.size) })
      ]);
      list.appendChild(item);
    });
    card.appendChild(list);

    $("#heroNote").textContent = "Version " + release.tag_name + (detected ? " for " + cfg.platforms[detected].label : "");
  }

  function loadRelease() {
    var card = $("#releaseCard");
    var cacheKey = "lc3kit-latest-release";
    $("#heroNote").textContent = "Version " + cfg.fallbackVersion;

    try {
      var cached = JSON.parse(sessionStorage.getItem(cacheKey) || "null");
      if (cached && Date.now() - cached.time < 600000) {
        renderRelease(card, cached.data);
        return;
      }
    } catch (error) { }

    fetch("https://api.github.com/repos/" + cfg.repo + "/releases/latest", {
      headers: { Accept: "application/vnd.github+json" }
    })
      .then(function (response) {
        if (response.status === 404) return null;
        if (!response.ok) throw new Error("status " + response.status);
        return response.json();
      })
      .then(function (data) {
        if (!data) {
          renderEmpty(card, "No release has been published yet.");
          return;
        }
        try {
          sessionStorage.setItem(cacheKey, JSON.stringify({ time: Date.now(), data: data }));
        } catch (error) { }
        renderRelease(card, data);
      })
      .catch(function () {
        renderEmpty(card, "The latest release could not be retrieved from GitHub.");
      });
  }

  setupLinks();
  setupInstitutions();
  setupNav();
  setupTour();
  setupBuild();
  loadRelease();
})();
