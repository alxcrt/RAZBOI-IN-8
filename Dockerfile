# Coolify / any Docker host: the prebuilt web/ folder plus web/dev.mjs serving it and /api/jev.
# Set AI_GATEWAY_API_KEY in the environment.
FROM node:24-alpine
WORKDIR /app
COPY web/ ./
ENV HOST=0.0.0.0 PORT=3000
EXPOSE 3000
USER node
CMD ["node", "dev.mjs"]
