#include "engine/prehistoric/core/util/Includes.hpp"
#include "GLFramebuffer.h"

#include "engine/platform/opengl/texture/GLTexture.h"

GLFramebuffer::GLFramebuffer(Window* window)
	: Framebuffer(window)
{
	glGenFramebuffers(1, &id);
	depthAttachment = -1;
}

GLFramebuffer::~GLFramebuffer()
{
	if (depthAttachment == -1)
		glDeleteRenderbuffers(1, &depthAttachment);

	glDeleteFramebuffers(1, &id);
}

void GLFramebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void GLFramebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFramebuffer::Clear(const Vector4f& colour)
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFramebuffer::SetDrawAttachments(uint32_t attachments ...)
{
	glDrawBuffers(sizeof(attachments) / sizeof(uint32_t), &attachments);
}

void GLFramebuffer::addDepthAttachment(uint32_t width, uint32_t height)
{
	glGenRenderbuffers(1, &depthAttachment);

	glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthAttachment);
}

void GLFramebuffer::addColourAttachment2D(Texture* texture, uint32_t attachment, uint32_t mipLevel)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, static_cast<GLTexture*>(texture)->getTextureID(), mipLevel);
}

void GLFramebuffer::addColourAttachment3D(Texture* texture, uint32_t face, uint32_t attachment, uint32_t mipLevel)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, static_cast<GLTexture*>(texture)->getTextureID(), mipLevel);
}

void GLFramebuffer::Blit(Framebuffer* destination, uint32_t width, uint32_t height, uint32_t source_attachment, uint32_t dest_attachment)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLFramebuffer*>(destination)->id);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + source_attachment);
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + dest_attachment);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
