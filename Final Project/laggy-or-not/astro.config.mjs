import { defineConfig } from "astro/config";
import react from "@astrojs/react";

import tailwind from "@astrojs/tailwind";

// https://astro.build/config
export default defineConfig({
  site: "https://tsuramii.github.io",
  base: "laggy-or-not",
  integrations: [
    react(),
    tailwind({
      applyBaseStyles: false,
    }),
  ],
});
